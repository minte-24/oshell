# 🔐 OShell — Custom Unix-Like Shell in C


## 📌 Overview
OShell is a custom Unix-like command-line shell implemented in C.  
It replicates core shell functionality including command execution, parsing, process control, and inter-process communication.

This project demonstrates low-level operating system concepts and provides insight into how commands are executed internally in Unix-based systems.

---

## 🚀 Features

- Interactive shell mode
- Batch (file-based) execution
- Command parsing and execution
- Built-in commands (cd, exit, env, setenv, unsetenv, alias, path)
- Environment variable expansion (`$VAR`, `$?`, `$$`)
- Command operators:
  - `;` sequential execution
  - `&&` conditional execution (success)
  - `||` conditional execution (failure)
  - `&` parallel execution
- Output redirection (`>`)
- Piping support
- Signal handling (Ctrl+C, Ctrl+D)

---

## 🧠 Core Concepts Demonstrated

- Process creation (`fork`)
- Program execution (`exec`)
- Process synchronization (`wait`)
- File descriptor manipulation
- Command parsing
- Environment variable management
- Signal handling

---

## 🛠️ Project Structure
oshell/
├── src/
├── include/
├── man/
├── examples/
│   └── basic.txt
├── README.md
├── AUTHORS.md
├── Makefile
├── .gitignore
