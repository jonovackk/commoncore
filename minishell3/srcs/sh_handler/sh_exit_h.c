#include "../../includes/minishell.h"

extern int  g_exit_code;

long    exit_atoi(char *str)
{
    long    n;
    int     sign;

    n = 0;
    sign = 0;
    while (ft_isspace(*str))
        str++;
    if (*str == '-' || *str == '+')
        sign = (*(str++) == '-');
    while (ft_isdigit(*str))
        n = n * 10 + (*str++ - '0');
    if (sign)
        return ((256 - n) % 256);
    return (n % 256);
}

void    exit_manager(int exit_code, error_t ec, t_sh_cmd *cmd)
{
    char    *msg;

    if (ec == ERR_NAN)
    {
        msg = ft_strjoin("exit: ", cmd->arguments[1], NULL, 0b00);
        print_error_message(ERR_NAN, msg);
        free(msg);
    }
    if (ec = ERR_ARGS)
    {
        print_error_message(ERR_ARGS, "exit");
        return;
    }
    rl_clear_history();
    if (cmd)
        sh_destroy_env_list(*(cmd->environment));
    sh_destroy_tree(get_tree_holder(0, NULL));
    exit(exit_code);
}

int     exit_builtin(t_sh_cmd *cmd)
{
    int     argc;

    argc = 0;
    if (cmd)
        argc = array_len(cmd->arguments) - 1;
    else
        ft_dprintf(2, "exit\n");
    if (!cmd || !argc)
        exit_manager(g_exit_code, ERR_NONE, cmd);
    if (!is_numeric(cmd->arguments[1]))
        exit_manager(ERR_GEN, ERR_NAN, cmd);
    if (argc > 1)
        exit_manager(ERR_FAIL, ERR_ARGS, cmd);
    else
        exit_manager(exit_atoi(cmd->arguments[1]), ERR_NONE, cmd);
    return (argc > 1);
}