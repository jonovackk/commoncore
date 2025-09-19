
# Minishell

Minishell is a simplified Unix shell developed as part of the Common Core at 42 Luxembourg.  
It interprets and executes user commands, replicating core features of well-known shells like `bash` and `zsh`.

## Features

- Execution of basic Unix commands
- Built-in commands: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`
- Input parsing with support for quotes and environment variables
- I/O redirection: `<`, `>`, `>>`
- Pipelines (`|`) for command chaining
- Signal handling (`Ctrl+C`, `Ctrl+\`, `EOF`)
- Custom prompt display
- Error handling and memory management

## How to Build and Run

1. **Clone or download the repository**
2. **Compile the project**:
   ```
   make
   ```
3. **Run the shell**:
   ```
   ./minishell
   ```

## Dependencies

- Standard C Library
- Unix/Linux environment
- `make` and `gcc`

## Project Structure

```
.
├── Makefile             # Build script
├── includes/            # Header files
├── libft/               # Custom C library (libft)
├── sources/             # Main source files for shell logic
└── minishell            # Executable created after compilation
```

## Authors

- [jnovack]
- [brunmart](https://github.com/BMarques21)  

Project developed as part of the 42 Network curriculum at **42 Luxembourg**.

## License

This project is open source and available under the [MIT License](https://opensource.org/licenses/MIT).
