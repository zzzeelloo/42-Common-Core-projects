### Dossier `src/exec` — Plan d’exécution et fonctions

Ce document décrit le déroulement complet de l’exécution dans le dossier `src/exec`, depuis la ligne saisie par l’utilisateur jusqu’à l’exécution d’une commande unique ou d’un pipeline. Les fonctions sont listées dans l’ordre logique d’appel, avec un résumé de leur rôle.

## Vue d’ensemble du flux
- **Entrée**: une ligne utilisateur (string)
- **Parsing**: tokenisation, validation syntaxique, expansions, conversion en tableau de tokens
- **Découpage**: création des groupes par `|` et collecte des redirections
- **Choix d’exécution**:
  - Une seule commande → branche « single »
  - Plusieurs groupes → branche « pipeline »
  - Aucun groupe mais redirections → ouverture/fermeture des fichiers pour side-effects
- **Exécution**:
  - Single: redirections + builtin/externe + attente
  - Pipeline: initialisation, boucle fork/pipe, redirections par processus, exec, attente, nettoyage

## Déroulement détaillé (fonction par fonction)

### 1) Point d’entrée: `command_processor.c`
- `process_command_line(user_input, envp)`
  - Appelle `parse_and_validate_input` pour obtenir une liste chainée d’éléments (tokens enrichis).
  - Appelle `expand_and_convert_elements` pour expansions de variables et conversion en `char **`.
  - Si `has_variable_assignment(...)` → applique `process_variable_assignments(...)`, libère et s’arrête.
  - Appelle `split_pipeline_groups(&exec, array_all_token)` pour remplir `exec.groups` et `exec.cmd_redirs`.
  - Compte les groupes, puis:
    - `handle_single_command(&exec, envp)` si 1 groupe
    - `handle_pipeline(&exec, group_count, envp)` si >1 groupe
    - `handle_empty_group_redirections(&exec, envp)` si 0 commande mais redirections présentes
  - Termine par libération des ressources.

- `parse_and_validate_input(user_input)` (dans `command_processor_utils.c`)
  - `tokenize_command_line` → `validate_syntax` → retourne la liste ou NULL.

- `expand_and_convert_elements(list, envp)` (dans `command_processor_utils.c`)
  - `process_variable_expansions` → `convert_elements_to_string_array` → tableau de tokens final.

- `handle_empty_group_redirections(exec, envp)`
  - Initialise pipex minimal, ouvre les fichiers d’IO via `open_files_for_single_command` pour appliquer l’effet des redirections sans commande, puis referme/nettoie.

### 2) Découpage en groupes et redirections
- `split_pipeline_groups(exec, tokens)` (dans `split_pipeline_group.c`)
  - `init_exec(exec)` → compte pipes/redirections via `redirections_and_tokens` → initialise `exec.cmd_redirs` pour chaque commande → alloue `exec.groups` et `exec.cmds` → `split_groups(exec, tokens)` → finalise dernier groupe.

- `redirections_and_tokens(exec, tokens)`
  - `count_pipes(tokens)` → fixe `exec.total_commands` à `pipes + 1`
  - `count_redirections(exec, tokens)` pour statistiques.

- `init_cmd_redirections(exec, total_commands)`
  - Alloue et initialise chaque `t_cmd_redir` (infile/outfile, append, fds, heredoc...).

- `split_groups(exec, tokens)` (dans `split_group.c`)
  - Parcourt les tokens et, selon le symbole:
    - `<<` → `is_heredoc`
    - `<` → `is_infile`
    - `>`/`>>` → `is_outfile`
    - `|` → séparation de groupe via `handle_pipe`
    - sinon → `is_notpipe` (ajoute le token courant aux `cmds` du groupe en cours)

- `is_infile / is_outfile / is_notpipe / is_heredoc` (dans `split_group_utils.c`)
  - Délèguent à `assign_infile_redirection`, `assign_outfile_redirection`, `assign_heredoc_redirection` ou dupliquent le token.

- `assign_infile_redirection(exec, tokens)` (dans `split_group.c`)
  - Enregistre le nom du fichier d’entrée dans `exec->cmd_redirs[ng]`.

- `assign_outfile_redirection(exec, tokens)` (dans `split_group.c`)
  - Crée/vidange le fichier si besoin, mémorise le nom et le mode `append`.

- `assign_heredoc_redirection(exec, tokens)` (dans `here_doc_utils.c`)
  - Nettoie un heredoc précédent, stocke le délimiteur, crée un pipe via `create_heredoc_pipe` et marque `is_heredoc`.

- `finalize_group(exec)` (dans `finalize_group.c`)
  - Fige les `cmds` collectés en un `char **group` (terminé par NULL) et l’ajoute à `exec.groups`.

### 3) Ouverture des fichiers (single/pipeline)
- `open_files_for_single_command(exec)` (dans `file_redirections.c`)
  - Ouvre `infile_fd` si `infile` valide et lisible, sinon message/`g_exit_status`.
  - Ouvre `outfile_fd` en mode append/trunc selon `append`.

- `open_files_for_pipeline(exec, group_count)` (dans `utils_bonus_2.c`)
  - Pour chaque commande i: ouvre `infile_fd` et `outfile_fd` selon `cmd_redirs[i]`.

### 4) Branche single: `exec_one.c` et utilitaires
- `handle_single_command(exec, envp)`
  - `setup_single_command_basic` → initialise pipex, alloue `pids[1]`, `open_files_for_single_command`.
  - `execute_single_command_logic`:
    - Si `env` avec argument → message d’erreur (cas spécial)
    - Si builtin → `handle_builtin_execution`
    - Sinon → `handle_external_command_execution`
  - Nettoyage: ferme fds heredoc/in/out et libère `pipex`.

- `setup_input_redirection_one / setup_output_redirection_one` (dans `exec_one_utils.c`)
  - Applique `dup2` depuis `heredoc_fd`/`infile_fd` vers `STDIN`, et `outfile_fd` vers `STDOUT`, si présents.

- `handle_builtin_execution(exec, envp)` (dans `exec_one_utils.c`)
  - Sauvegarde `stdin/stdout`, applique redirections avec `apply_redirections_for_builtin`, exécute `execute_builtin`, puis restaure FDs.

- `handle_external_command_execution(exec, envp)` (dans `exec_one.c`)
  - `exec_one` fork, applique redirections, `execute_bonus_args` dans l’enfant.
  - Le parent ignore `SIGINT`, `waitpid`, puis met à jour `g_exit_status`.

- `apply_redirections_for_builtin / restore_original_fds` (dans `file_redirections.c`)
  - Duplication/restauration des FDs pour exécuter un builtin avec redirections.

### 5) Branche pipeline: `pipeline_manager.c` et `setup_pipeline.c`
- `handle_pipeline(exec, group_count, envp)`
  - 1) `initialize_pipeline` → `pipex_init`, alloue `pids[group_count]`, `open_files_for_pipeline`.
  - 2) `execute_pipeline_commands` → boucle sur i:
    - Crée un `pipe` si nécessaire
    - `setup_pipe_descriptors(exec, i, group_count, prev_pipe_read, pipe_fd)` pour définir `fd[0]`/`fd[1]` côté enfant
    - `create_child_process(exec, i, envp)` → fork, enfant: `setup_redirections` puis `execute_bonus_args`
    - Parent: ferme extrémités inutiles et met à jour `prev_pipe_read`
  - 3) `finalize_pipeline` → ignore `SIGINT`, `waitpid` sur tous, met à jour `g_exit_status` selon la dernière commande, `signals_monitoring`, nettoie tous les heredocs, libère `pids` et `paths`.

- `setup_pipe_descriptors_*` (dans `setup_pipeline.c`)
  - Cas premier/milieu/dernier: renseigne `exec->pipex.fd[0]` (entrée) et `fd[1]` (sortie) à partir des pipes.

- `setup_redirections(exec)` (dans `child_process.c`)
  - Entrée: priorise `heredoc_fd` puis `infile_fd`, sinon, si présent, lit depuis `fd[0]` (pipe précédent).
  - Sortie: priorise `outfile_fd`, sinon écrit vers `fd[1]` (pipe suivant).
  - Ferme les descripteurs de pipe locaux.

- `execute_bonus_args(exec, cmd_args, envp)` (dans `exec_bonus.c`)
  - Si builtin → exécute directement et met `g_exit_status`.
  - Sinon: `find_path` (PATH ou chemin direct), vérifie fichiers/droits, `check_if_directory`, puis `execve`.

### 6) Here-Doc: `here_doc.c` et utilitaires
- `create_heredoc_pipe(delimiter)`
  - Crée un pipe, lit des lignes jusqu’au délimiteur (via `readline("> ")`), écrit dans `pipe[1]`, retourne `pipe[0]` pour l’entrée de la commande.

- `cleanup_heredoc(cmd_redir)` / `cleanup_all_heredocs(exec)`
  - Libère le délimiteur, ferme `heredoc_fd`, remet les flags à zéro pour un ou tous les `t_cmd_redir`.

- `assign_heredoc_redirection(exec, tokens)` (dans `here_doc_utils.c`)
  - Prépare les champs heredoc pour la commande courante (`ng`).

### 7) Utilitaires Exec: `utils_bonus.c` / `utils_bonus_2.c`
- `pipex_init(exec, envp)`
  - Initialise la structure `exec->pipex`, détecte `PATH` et découpe `paths`.

- `find_path(exec, cmd)`
  - Cherche un exécutable via PATH; sinon accepte un chemin absolu/relatif; vérifie droits d’exécution.

- `check_exec_file / check_exec / check_if_directory / handle_execve_error`
  - Vérifient existence, droits, directory vs fichier, et gèrent les erreurs d’`execve` avec les bons codes.

### 8) Cycle de vie d’une ligne de commande (résumé)
1. `process_command_line` → parse/validate/expand → tokens
2. `split_pipeline_groups` → `groups` et `cmd_redirs` prêts
3. Choix:
   - 1 groupe: `handle_single_command`
   - N>1 groupes: `handle_pipeline`
   - 0 commande mais redirections: `handle_empty_group_redirections`
4. Ouverture des fichiers/redirections (`open_files_*`, `setup_*redirection*`)
5. Exécution builtin/execve → attente → `g_exit_status`
6. Nettoyage (heredocs, fds, `pipex`, `paths`)

## Points d’attention
- Les redirections priment sur les pipes lorsqu’elles sont définies pour une commande.
- Les builtins en single sont exécutés dans le processus parent (avec duplication/restauration de FDs) pour préserver l’environnement.
- `g_exit_status` est mis à jour par la dernière commande du pipeline ou par le builtin/execve exécuté. 