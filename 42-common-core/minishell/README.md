[← Back to 42 Common Core](../README.md)

*This project has been created as part of the 42 curriculum by anpetit, zcherif.*

# minishell

[![42](https://img.shields.io/badge/42-Project-blue)](https://42.fr)
[![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))

A small Bash-like shell written in C. It reads a command line with GNU Readline, parses it, expands it and runs it with pipes and redirections, the way Bash does.

## Features

- Interactive prompt with history (GNU Readline)
- Pipes: `cmd1 | cmd2 | cmd3`
- Redirections: `<`, `>`, `>>` and heredoc `<<`
- Single and double quotes, with `$VAR` and `$?` expansion
- Command lookup in `PATH`, absolute and relative paths
- Built-ins: `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Signals: `Ctrl-C` shows a new prompt, `Ctrl-D` exits, `Ctrl-\` is ignored
- Syntax errors reported like Bash (`syntax error near unexpected token`)

## Architecture

```
input ──▶ lexer ──▶ syntax check ──▶ expansion ──▶ command list ──▶ executor
          (tokens)                   ($VAR, quotes)                 (fork, pipe, dup2, execve)
```

| Folder | Role |
|---|---|
| `src/parsing/` | Lexical analysis, operator handling, syntax validation, variable expansion, quote removal |
| `src/exec/` | Pipeline setup, child processes, redirections, heredocs, cleanup |
| `src/builtins/` | Built-in commands run in the parent process when needed |
| `src/utils/` | Environment management, signals, memory and file-descriptor cleanup |

More detail (in French): [README_FONCTIONNEMENT.md](./README_FONCTIONNEMENT.md), [PARSING_README.md](./PARSING_README.md), [EXEC_README.md](./EXEC_README.md).

## Build and run

Requires the GNU Readline development library (`libreadline-dev` on Debian/Ubuntu).

```bash
make
./minishell
```

Check for leaks while ignoring Readline's own allocations:

```bash
valgrind --suppressions=readline.supp --leak-check=full ./minishell
```

## Team

- **anpetit**
- **zcherif**
