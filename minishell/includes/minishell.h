#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>

# include <stdio.h>

# include <stdarg.h>

# include <errno.h>

# include <stdlib.h>

# include <signal.h>

# include <fcntl.h>

# include <readline/readline.h>

# include <readline/history.h>

# include <sys/types.h>

# include <sys/wait.h>

# include <sys/stat.h>

# include <termios.h>

# include <dirent.h>

# include "../libft/includes/libft.h"

# include "sh_handler.h"

# include "sh_input_parser.h"

# include "sh_managers.h"

# include "sh_operators.h"

# include "sh_enumerates.h"



/* Prefixos de Mensagens */
#define PROMPT_SUCCESS "\001\033[32;1m\002$?\001\033[0m\002 "
#define PROMPT_FAIL "\001\033[31;1m\002$?\001\033[0m\002 "
#define PROMPT_TAIL "\001\033[37;1m\002Minishell$\001\033[0m\002 "
#define PROMPT_SINGLE_DQUOTE "\001\033[36;1m\002'' dquote:\001\033[0m\002 > "
#define PROMPT_DOUBLE_DQUOTE "\001\033[34;1m\002\"\" dquote:\001\033[0m\002 > "
#define PROMPT_HEREDOC "\001\033[35;1m\002HD here-doc:\001\033[0m\002 > "
#define PROMPT_ERROR "\001\033[31;1m\002/!\\ ERROR! > "
#define PROMPT_WARNING "\001\033[33;1m\002/!\\ WARNING! > "

/* Mensagens de Erro */
#define ERR_MSG_VAR_NOT_SET "%scd: %s not set\n"
#define ERR_MSG_NO_SUCH_FILE_OR_DIR "%s%s: no such file or directory\n"
#define ERR_MSG_TOO_MANY_ARGS "%s%s: too many arguments\n"
#define ERR_MSG_NUMERIC_ARG_REQUIRED "%s%s: numeric argument required\n"
#define ERR_MSG_INVALID_IDENTIFIER "%sexport: `%s': not a valid identifier\n"
#define ERR_MSG_PERMISSION_DENIED "%s%s: Permission denied\n"
#define ERR_MSG_IS_A_DIRECTORY "%s%s: Is a directory\n"
#define ERR_MSG_INVALID_OPTION "%s%s: Invalid option\n"
#define ERR_MSG_HEREDOC_EOF "%s here-document delimited by end-of-file (wanted `%s')\n"
#define ERR_MSG_UNEXPECTED_EOF "%sunexpected EOF while looking for matching `%s'\n"
#define ERR_MSG_SYNTAX_ERROR_QUOTE "%ssyntax error%s\n"
#define ERR_MSG_SYNTAX_ERROR_TOKEN "%ssyntax error near unexpected token `%s'\n"
#define ERR_MSG_SYNTAX_ERROR "%ssyntax error\n"
#define ERR_MSG_HEREDOC_LIMIT_EXCEEDED "%smaximum here-document count exceeded\n"
#define ERR_MSG_NO_MORE_FDS "%s%s: no more fds. Aborting\n"
#define ERR_MSG_AMBIGUOUS_REDIRECT "%s%s: ambiguous redirect\n"

/* Modos de Abertura de Arquivos */
#ifndef FILE_MODE_READ
#define FILE_MODE_READ 00 /* O_RDONLY */
#endif

#ifndef FILE_MODE_WRITE_CREATE
#define FILE_MODE_WRITE_CREATE 01101 /* O_WRONLY | O_CREAT | O_TRUNC */
#endif

#ifndef FILE_MODE_WRITE_APPEND
#define FILE_MODE_WRITE_APPEND 02101 /* O_WRONLY | O_CREAT | O_APPEND */
#endif

#ifndef FILE_MODE_WRITE_EXCLUSIVE
#define FILE_MODE_WRITE_EXCLUSIVE 01301 /* O_WRONLY | O_EXCL | O_CREAT | O_TRUNC */
#endif

#endif