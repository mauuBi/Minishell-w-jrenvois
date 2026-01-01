# Minishell - Hours of hours of comparing with reel SHELL

## Introduction
Minishell is a landmark project in the **42 Paris** curriculum. It marks the transition from simple algorithmics to true **System Programming**. The goal was to recreate a simplified version of Bash, handling everything from command parsing to execution logic and environment management.

This project was a deep dive into the Unix philosophy: *"Write programs that do one thing and do it well. Write programs to work together."*

---

## Architecture & Logic

The project is divided into four main stages:

### 1. The Lexer & Parser
- **Tokenization:** Breaking the input string into meaningful tokens (Words, Pipes, Redirections).
- **Grammar:** Handling double quotes `"` (variable expansion allowed) and single quotes `'` (literal string).
- **Syntax Error Handling:** Detecting unclosed quotes or misplaced redirection operators before execution.

### 2. The Expander
- **Variable Substitution:** Replacing `$VAR` with its value from the environment.
- **Exit Status:** Handling the special `$?` variable to fetch the last command's return code.

### 3. The Executor
- **Pipe Management:** Creating a pipeline of processes where the `stdout` of one command becomes the `stdin` of the next.
- **Redirections:** Using `dup2` to redirect file descriptors for `<`, `>`, `>>`, and `<<` (heredoc).
- **Path Resolution:** Searching for binary executables in the `PATH` environment variable.

### 4. Built-in Commands
We re-implemented the following from scratch:
- `echo` (with `-n` option)
- `cd` (updating `PWD` and `OLDPWD`)
- `pwd`, `export`, `unset`, `env`, `exit`

---

## Key Technical Challenges

### Process Orchestration
Managing multiple children processes simultaneously while ensuring the parent shell remains responsive and handles signals correctly. We had to be extremely careful with `waitpid` to avoid hangs or "zombie" processes.

### Memory Integrity
In a shell, a memory leak isn't just a mistake—it's a crash waiting to happen over time. Our Minishell was tested with `Valgrind` to ensure **zero leaks**, even after complex pipelines or syntax errors.

### Signal Handling
Implementing a global state or specific logic to ensure `Ctrl-C` (SIGINT), `Ctrl-\` (SIGQUIT), and `Ctrl-D` (EOF) behave exactly like in a real Bash session (e.g., interrupting a child process without killing the shell).

---

## Getting Started

### Prerequisites
- A Unix-based system (Linux/macOS).
- `gcc` or `clang` compiler.
- `readline` library.

### Installation
```bash
# Clone the repository
git clone [https://github.com/YourUser/minishell.git](https://github.com/YourUser/minishell.git)
cd minishell

# Compile the project
make
