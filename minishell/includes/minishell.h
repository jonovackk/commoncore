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

# include "ft_enumerates.h"



/*PROMPTS ******************************************** */

# define RD_APPENDS "\001\033[32;1m\002$?\001\033[0m\002 "

# define RD_INFILES "\001\033[31;1m\002$?\001\033[0m\002 "

# define RD_OUTPUTS "\001\033[37;1m\002 Minishell$\001\033[0m\002 "

# define QU_ZERO "\001\033[36;1m\002''  dquote:\001\033[0m\002 > "

# define P_DDQUOTE "\001\033[34;1m\002\"\"  dquote:\001\033[0m\002 > "

# define RD_HEREDOC "\001\033[35;1m\002HD  here-doc:\001\033[0m\002 > "

# define P_ERROR "\001\033[31;1m\002/!\\ ERROR! > "

# define P_WARNING "\001\033[33;1m\002/!\\ WARNING! > "


/* ********************************************** */

# define ES_NOTSET "%scd: %s not set\n"

# define ES_NOFORD "%s%s no such file or directory\n"

# define ES_TMARGS "%s%s: too many arguments\n"

# define ES_NOTNUM "%s%s: numeric argument required\n"

# define ES_NOTVAL "%sexport: `%s': not a valid identifier\n"

# define ES_NOPERM "%s%s: Permission denied\n"

# define ES_ISADIR "%s%s: Is a directory\n"

# define ES_INVOPT "%s%s: Invalid option\n"

# define ES_HDSTOP "%s here-document delimited by end-of-file, (wanted `%s')\n"

# define ES_DQSTOP "%sunexpected EOF while looking for matching `%s\'\n"

# define ES_SYNTXQ "%ssyntax error%s\n"

# define ES_SYNTXT "%ssyntax error near unexcepted token `%s'\n"

# define ES_SYNTXL "%ssyntax error\n"

# define ES_HLIMIT "%smaximum here-document count exceeded\n"

# define ES_INVFDS "%s%s: no more fds. Aborting\n"

# define ES_AMBRED "%s%s: ambiguous redirect\n"

/* OPENING MODES ************************************************************ */

// O_RDONLY = 00
# ifndef OPEN_READ
#  define OPEN_READ 00
# endif

// O_WRONLY = 01 | O_CREAT = 0100 | O_TRUNC = 01000
# ifndef OPEN_CREATE
#  define OPEN_CREATE 01101
# endif

// O_WRONLY = 01 | O_CREAT = 0100 | O_APPEND = 02000
# ifndef OPEN_APPEND
#  define OPEN_APPEND 02101
# endif

// O_WRONLY = 01 | O_EXCL = 0200 | O_CREAT = 0100 | O_TRUNC = 01000
# ifndef OPEN_EXCL
#  define OPEN_EXCL 01301

# endif