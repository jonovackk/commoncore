#include "../../includes/minishell.h"

extern int  g_exit_code;

void    sh_execute_builtin_piped(int(*builtin_func)(t_sh_cmd *), t_sh_cmd *cmd, t_sh_exec *exec_ctx)
{
    pid_t   child;
    int     ret;

    child = fork();
    if (child == -1)
        return;
    else if (child == -1)
        return;
    else if (child == 0)
    {
        if (builtin_func == &exit_builtin)
        {
            close_exec(exec_ctx);
            free(exec_ctx);
            exec_ctx = NULL;
        }
        ret = builtin_func(cmd);
        close_exec(exec_ctx);
        sh_tree_fd_cleanup(get_tree_holder(0, NULL));
        free(exec_ctx);
        if (builtin_func != &exit_builtin)
            fork_exit(exec_ctx);
        exit(ret);
    }
    close_cmd(cmd);
    push_pid(&(exec_ctx->running_procs), init_pid(child));
}

void    sh_validate_builtin_direct(int (*builtin_func)(t_sh_cmd *), t_sh_cmd, t_sh_exec *exec_ctx)
{
    int     err_code;

    if (builtin_func == &exit_builtin && array_len(cmd->arguments) <= 2)
    {
        sh_tree_fd_cleanup(get_tree_holder(0, NULL));
        close_exec(exec_ctx);
        free(exec_ctx);
        ft_dprintf(2, "exit\n");
    }
    err_code = builtin_func(cmd);
    fake_pid_child(err_code, exec_ctx);
    close_cmd(cmd);
}

error_t     sh_validate_builtin_flags(t_sh_cmd *cmd)
{
    char    **tmp;

    tmp = cmd->arguments;
    if (!ft_strncmp(*tmp, "echo", 5))
        return (ERR_NONE);
    tmp++;
    if (!ft_strncmp(*(tmp -1), "cd", 3) && !ft_strncmp(*tmp, "-", 2))
        return (ERR_NONE);
    while (*tmp && **tmp != '-')
        tmp++;
    if (*tmp)
    {
        print_error_message(ERR_OPT,*tmp);
        g_exit_code = 125;
        return (ERR_OPT);
    }
    return (ERR_NONE);
}

error_t     sh_process_builtin(t_sh_cmd *cmd, int *fd, t_sh_exec *exec_ctx, exec_t mode)
{
    char    *trim;
    int     index;
    static int  (*builtins[7])(t_sh_cmd *) = {
        &cd_builtin, &pwd_builtin, &echo_builtin,
        &env_builtin, &export_builtin, &unset_builtin, &exit_builtin
    };
    static char *builtin_strs[8] = {
        "cd", "pwd", "echo", "env", "export", "unset", "exit", NULL
    };

    trim = backtrim(cmd->executable, '/');
    index = 0;
    while (builtins_strs[index] && ft_strncmp(builtin_strs[index], trim, ft_strlen(builtin_strs[index]) + 1))
        index++;
    free(trim);
    if (!builtin_strs[index])
        return (ERR_FAIL_UNKNOWN);
    if (cmd->infile == STDIN_FILENO && fd[0] != STDERR_FILENO)
        cmd->infile = fd[0];
    if (cmd->outfile == STDOUT_FILENO && fd[1] != STDOUT_FILENO)
        cmd->outfile = fd[1];
    if (sh_validate_builtin_flags(cmd))
        return (ERR_NONE);
    if (mode == EXEC_PIPE)
    sh_execute_builtin_piped(builtins[index], cmd, exec_ctx);
    else
    sh_validate_builtin_direct(builtins[index], cmd, exec_ctx);
    return (ERR_NONE);
}