# Guide du Parsing - Minishell

## Vue d'ensemble

Ce document explique en détail le processus de parsing de votre minishell, qui transforme une ligne de commande brute en une structure de données exploitable pour l'exécution. Le parsing se déroule en plusieurs phases distinctes et bien organisées.

## Architecture générale

Le parsing suit cette séquence :
1. **Analyse lexicale** (01_*) - Découpage en tokens
2. **Traitement des opérateurs** (02_*) - Reconnaissance des redirections et pipes
3. **Validation syntaxique** (03_*) - Vérification de la grammaire
4. **Expansion des variables** (04_*) - Traitement des $VAR et $?
5. **Construction de chaînes** (05_*) - Assemblage final
6. **Conversion finale** (06_*) - Transformation en format d'exécution

## Structures de données principales

### t_parse_element
```c
typedef struct s_parse_element
{
    char                    *text;          // Texte final après expansion
    t_element_kind          kind;           // Type d'élément (WORD, PIPE, etc.)
    t_quote_style           quote_mode;     // Style de guillemets
    t_text_fragment         *fragments;     // Fragments originaux
    struct s_parse_element  *next;          // Élément suivant
} t_parse_element;
```

### t_text_fragment
```c
typedef struct s_text_fragment
{
    char                    *content;       // Contenu du fragment
    t_quote_style           style;          // QUOTE_NONE, QUOTE_SINGLE, QUOTE_DOUBLE
    struct s_text_fragment  *next;          // Fragment suivant
} t_text_fragment;
```

### t_str_builder
```c
typedef struct s_str_builder
{
    char            *str;                   // Chaîne en construction
    size_t          len;                    // Longueur actuelle
} t_str_builder;
```

## Phase 1 : Analyse lexicale (01_*)

### 1.1 Point d'entrée principal (`01_0_lexical_core.c`)

**Fonction clé :** `tokenize_command_line()`

```c
t_parse_element *tokenize_command_line(const char *input_line)
```

**Processus :**
1. Ignore les espaces en début de ligne
2. Pour chaque caractère non-espace :
   - Si c'est un opérateur → `process_operator_element()`
   - Si c'est le début d'un mot → `process_word_element()`
   - Sinon → erreur de syntaxe

### 1.2 Utilitaires lexicaux (`01_1_lexical_utils.c`)

**Fonctions de classification :**
- `char_is_space()` : Détecte espaces, tabs, newlines
- `char_is_word_start()` : Détermine si un caractère peut commencer un mot
- `char_is_operator_start()` : Identifie les opérateurs (|, <, >, ;, &, (, ))

### 1.3 Traitement des mots (`01_2_word_processing.c`)

**Gestion des caractères échappés :**
```c
int handle_escaped_char(const char **line_ptr, t_str_builder *sb, int *status)
```
- Traite `\$` → `$` littéral
- Traite `\c` → `c` littéral

**Parsing des caractères non-cités :**
```c
int parse_unquoted_chars(const char **line_ptr, t_str_builder *sb, int *status)
```
- Lit jusqu'à rencontrer un opérateur ou une quote
- Gère l'échappement avec `\`

### 1.4 Éléments de mots (`01_3_word_element.c`)

**Traitement des fragments cités :**
```c
int process_quoted_fragment(const char **line_ptr, t_text_fragment **fragments_head, int *status)
```
- Extrait le contenu entre guillemets
- Crée un fragment avec le bon style de quote

**Traitement des fragments non-cités :**
```c
int process_unquoted_fragment(const char **line_ptr, t_text_fragment **fragments_head, int *status)
```
- Utilise un string builder pour accumuler les caractères
- Gère l'échappement

**Assemblage final :**
```c
int process_word_element(const char **line_ptr, t_parse_element **head)
```
- Combine tous les fragments d'un mot
- Crée un élément de type ELEM_WORD

## Phase 2 : Traitement des opérateurs (02_*)

### 2.1 Opérateurs généraux (`02_0_operator_processing.c`)

**Fonction principale :**
```c
int process_operator_element(const char **line_ptr, t_parse_element **head)
```

**Types d'opérateurs gérés :**
- `|` → ELEM_PIPE
- `;` → ELEM_SEMICOLON
- `&` → Erreur (non supporté)
- `(` `)` → Erreur (non supporté)

### 2.2 Redirections (`02_1_redirection_operators.c`)

**Redirections d'entrée :**
- `<` → ELEM_INPUT_REDIR
- `<<` → ELEM_HEREDOC_REDIR

**Redirections de sortie :**
- `>` → ELEM_OUTPUT_REDIR
- `>>` → ELEM_APPEND_REDIR

## Phase 3 : Validation syntaxique (03_*)

### 3.1 Validation générale (`03_0_syntax_validation.c`)

**Fonction principale :**
```c
int validate_syntax(t_parse_element *elements)
```

**Vérifications effectuées :**
1. **Séquence de début** : Pas d'opérateur en première position
2. **Séquences consécutives** : Pas de `||`, `;;`, `|;`, etc.
3. **Séquence de fin** : Pas d'opérateur en dernière position

### 3.2 Vérifications spécifiques (`03_1_syntax_checks.c`)

**Séquences invalides détectées :**
- `||` (double pipe)
- `;;` (double semicolon)
- `|;` ou `;|` (pipe suivi de semicolon)
- Redirections conflictuelles (`<` suivi de `>`)
- Redirections multiples du même type

## Phase 4 : Expansion des variables (04_*)

### 4.1 Point d'entrée (`04_0_variable_expansion.c`)

**Fonction principale :**
```c
char *expand_variables_in_str(const char *input_str, t_quote quote_type, char **envp, int last_exit_status)
```

**Processus :**
1. Parcourt la chaîne caractère par caractère
2. Détecte les `$` (variables)
3. Gère l'échappement `\$` → `$` littéral
4. Appelle l'expansion appropriée selon le contexte

### 4.2 Utilitaires variables (`04_1_variable_utilities.c`)

**Recherche dans l'environnement :**
```c
char *get_env_var_value(const char *var_name, char **envp, int last_exit_status)
```

**Variables spéciales :**
- `$?` → Code de sortie de la dernière commande
- `$UID` → UID de l'utilisateur actuel
- `$VAR` → Variable d'environnement standard

### 4.3 Gestionnaires de variables (`04_2_variable_handlers.c`)

**Types d'expansion supportés :**

1. **Statut de sortie :**
   ```c
   static char *handle_exit_status(const char **str_ptr, char **envp, int last_exit_status)
   ```
   - `$?` → Valeur de `g_exit_status`

2. **Variables avec accolades :**
   ```c
   static char *handle_braced_variable(const char **str_ptr, char **envp, int last_exit_status)
   ```
   - `${VAR}` → Variable d'environnement

3. **Variables basiques :**
   ```c
   static char *handle_basic_variable(const char **str_ptr, char **envp, int last_exit_status)
   ```
   - `$VAR` → Variable d'environnement

**Règles d'expansion :**
- Dans les guillemets simples (`'`) : **Aucune expansion**
- Dans les guillemets doubles (`"`) : **Expansion des variables**
- Sans guillemets : **Expansion des variables**

### 4.4 Processeur de variables (`04_2_variable_processor.c`)

**Fonction principale :**
```c
t_parse_element *process_variable_expansions(t_parse_element *input_elements, char **environment, int shell_exit_code)
```

**Processus :**
1. Parcourt tous les éléments parsés
2. Pour chaque élément WORD :
   - Traite chaque fragment selon son style de quote
   - Applique l'expansion des variables si nécessaire
3. **Exception spéciale :** Les mots après `<<` (heredoc) ne sont **pas** expansés

## Phase 5 : Construction de chaînes (05_*)

### 5.1 String Builder (`05_0_string_builder.c`)

**Structure pour construire des chaînes efficacement :**

```c
void sb_init(t_str_builder *sb)                    // Initialise
int sb_append_char(t_str_builder *sb, char c)      // Ajoute un caractère
int sb_append_str(t_str_builder *sb, const char *s) // Ajoute une chaîne
char *sb_to_string(t_str_builder *sb)              // Finalise et retourne
void sb_free(t_str_builder *sb)                    // Libère la mémoire
```

### 5.2 Traitement des guillemets (`05_1_quote_processing.c`)

**Extraction du contenu cité :**
```c
char *extract_quoted_content_new(const char **line_ptr, char quote_char, int *status)
```

**Gestion de l'échappement dans les guillemets doubles :**
- `\"` → `"` littéral
- `\\` → `\` littéral
- `\$` → `$` littéral
- `\`` → `` ` `` littéral

## Phase 6 : Conversion finale (06_*)

### 6.1 Conversion en tableau (`06_0_final_conversion.c`)

**Fonction principale :**
```c
char **convert_elements_to_string_array(t_parse_element *element_list)
```

**Processus :**
1. Compte le nombre d'éléments
2. Alloue un tableau de chaînes
3. Copie le texte de chaque élément
4. Retourne un tableau terminé par NULL

### 6.2 Gestion des éléments (`06_1_element_management.c`)

**Création de fragments :**
```c
t_text_fragment *create_text_fragment(char *content, t_quote_style style)
```

**Ajout d'éléments à la liste :**
```c
int add_element_to_list(t_parse_element **head, char *text, t_element_kind kind, t_quote_style quote_mode, t_text_fragment *fragments)
```

## Exemples de traitement

### Exemple 1 : Commande simple
```
Input: echo "Hello $USER"
```

**Phase 1 - Lexical :**
- `echo` → ELEM_WORD (fragment non-cité)
- `"Hello $USER"` → ELEM_WORD (fragment double-quoté)

**Phase 4 - Expansion :**
- `echo` → `echo` (pas d'expansion)
- `"Hello $USER"` → `"Hello angus"` (expansion de $USER)

**Résultat final :** `["echo", "Hello angus", NULL]`

### Exemple 2 : Avec échappement
```
Input: echo "Price: \$50"
```

**Phase 1 - Lexical :**
- `echo` → ELEM_WORD
- `"Price: \$50"` → ELEM_WORD (fragment double-quoté)

**Phase 4 - Expansion :**
- `"Price: \$50"` → `"Price: $50"` (échappement préservé)

**Résultat final :** `["echo", "Price: $50", NULL]`

### Exemple 3 : Heredoc
```
Input: cat << EOF
```

**Phase 1 - Lexical :**
- `cat` → ELEM_WORD
- `<<` → ELEM_HEREDOC_REDIR
- `EOF` → ELEM_WORD

**Phase 4 - Expansion :**
- `cat` → `cat`
- `<<` → `<<` (opérateur, pas d'expansion)
- `EOF` → `EOF` (après heredoc, pas d'expansion)

## Gestion des erreurs

### Types d'erreurs détectées :
1. **Erreurs de syntaxe :** Opérateurs invalides, séquences interdites
2. **Erreurs de mémoire :** Échec d'allocation
3. **Erreurs de parsing :** Guillemets non fermés, caractères inattendus

### Mécanisme de nettoyage :
- `cleanup_element_list()` : Libère toute la chaîne d'éléments
- `cleanup_fragments()` : Libère tous les fragments d'un élément
- `sb_free()` : Libère le string builder

## Points d'attention

1. **Gestion mémoire :** Chaque allocation est vérifiée et nettoyée en cas d'erreur
2. **Expansion conditionnelle :** Les variables ne sont expansées que dans les bons contextes
3. **Heredoc spécial :** Les délimiteurs de heredoc ne sont jamais expansés
4. **Échappement :** Géré différemment selon le contexte (guillemets simples vs doubles)
5. **Validation stricte :** Syntaxe vérifiée avant toute expansion

Ce système de parsing est robuste et suit les standards POSIX pour le traitement des shells.
