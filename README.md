# Custom Shell

A simple custom shell written in C, demonstrating process management, parsing, and basic built-in commands.

## 🚀 Features

- Command parsing
- Built-in functions
- Execution of external programs
- Dynamic prompt showing current working directory



main.c // Entry point, shell loop
shell.c // Shell logic: execute(), launch()
parser.c // Input reading and parsing
shell.h // Function declarations and includes
.gitignore // Ignore compiled binaries


## 🛠️ Compilation


gcc -o my_own_shell main.c shell.c parser.c
./my_own_shell



