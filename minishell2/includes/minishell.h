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

# include "ft_dt_struct.h"

# include "ft_parsing.h"

# include "ft_enumerates.h"

# include "ft_exec.h"



/*PROMPTS ******************************************** */

# define RD_APPENDS "\001\033[32;1m\002$?\001\033[0m\002 "

# define RD_INFILES "\001\033[31;1m\002$?\001\033[0m\002 "

# define RD_OUTPUTS "\001\033[37;1m\002 Minishell$\001\033[0m\002 "

# define QU_ZERO "\001\033[36;1m\002''  dquote:\001\033[0m\002 > "

# define P_DDQUOTE "\001\033[34;1m\002\"\"  dquote:\001\033[0m\002 > "

# define RD_HEREDOC "\001\033[35;1m\002HD  here-doc:\001\033[0m\002 > "

# define P_ERROR "\001\033[31;1m\002/!\\ ERROR! > "

# define P_WARNING "\001\033[33;1m\002/!\\ WARNING! > "



# endif