# Minishell (42 Project)

This is a simplified Unix shell written in C, developed as part of the 42 school curriculum. It mimics some basic behavior of bash, allowing users to execute commands, handle redirections, pipes, and environment variables, as well as manage signals gracefully.

## 👥 Collaboration

Project developed by [@Alima-T](https://github.com/Alima-T) and [@bolsakova](https://github.com/bolsakova).

## 🚀 Features

* Execution of built-in and external commands
* Command parsing and tokenization
* Environment variable management (`$VAR`, `export`, `unset`, etc.)
* Input/output redirection (`>`, `<`, `>>`)
* Pipes (`|`)
* Signal handling (e.g., `Ctrl+C`, `Ctrl+D`)
* Error handling with clear messages
* Memory leak prevention

## 🔧 Built-in Commands

* `cd`
* `echo`
* `env`
* `exit`
* `export`
* `pwd`
* `unset`

## 🛠️ Usage

1. Clone the repository:

   ```bash
   git clone https://github.com/Alima-T/minishell_42.git
   cd minishell_42
   ```
2. Compile the project:

   ```bash
   make
   ```
3. Run Minishell:

   ```bash
   ./minishell
   ```

## 🧪 Testing

You can test the shell with various combinations of built-in and external commands, redirections, and pipelines.

## 📜 License

This project is for educational purposes at 42 School.

---

Made with ❤️ at 42
