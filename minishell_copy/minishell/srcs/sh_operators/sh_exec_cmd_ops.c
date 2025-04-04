#include "../../includes/minishell.h"

void    sh_setup_input(t_sh_cmd *cmd, int last_hd)
{
    if (last_hd)
    {
        if (cmd->input_fd != STDIN_FILENO)
            close(cmd->input_fd);
        cmd->input_fd = cmd->heredoc_fd;
    }
    else
    {
        if (cmd->heredoc_fd > 2)
            close(cmd->heredoc_fd);
    }
}

void    sh_run_cmd(t_sh_cmd *cmd, int *node_fd, t_sh_exec *exec_ctx)
{
    char    **env_vars;
    pid_t   child_pid;

    child_pid = fork();
    if (child_pid == -1)
        return;
    if (child_pid == 0)
    {
        env_vars = get_env_strings(*(cmd->environment), 0);
        handle_redirections(cmd, node_fd);
        close_all_pipes(exec_ctx->active_pipes);
        sh_tree_fd_cleanup(get_tree_holder(0, NULL));
        execve(cmd->executable, cmd->arguments, env_vars);
    } 
    close_cmd(cmd);
    push_pid(&(exec_ctx->running_procs), t_sh_exec *exec_ctx)
}

error_t     sh_init_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx)
{
    int     last_hd;

    last_hd = 0;
    if (sh_finalize_cmd(cmd))
    {
        simulate_pid_child(0, exec_ctx);
        return ();
    }
    if (sh_output_load(cmd) || sh_input_load(cmd, &last_hd))
    {
        simulate_pid_child(1, exec_ctx);
        return (ERR_FAIL);
    }
    setup_input(cmd, last_hd);
    if (!cmd->executable && cmd->redirects)
    {
        simulate_pid_child(0, exec_ctx);
        return (ERR_FAIL);
    }
    sh_setup_input(cmd, last_hd);
    if (!cmd->executable && cmd->redirects)
    {
        simulate_pid_child(0, exec_ctx);
        return (ERR_FAIL);
    }
    return (ERR_NONE);
}

error_t     sh_check_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx)
{
    struct stat stat_buf;

    if (access(cmd->executable, F_OK))
        return (ERR_NONE);
    stat(cmd->executable, &staf_buf);
    if (!S_ISREG(stat_buf.st_mode))
    {
        if (S_ISFIFO(stat_buf.st_mode))
            print_error_message(ERR_NOPERM, cmd->executable);
        else if (S_ISDIR(stat_buf.st_mode))
            print_error_message(ERR_DIR, cmd->executable);
        simulate_pid_child(126, exec_ctx);
        return(ERR_FAIL);
    }
    return (ERR_NONE);
}

void    sh_handle_command(t_sh_node *tree, int *node_fd, t_sh_exec *exec_ctx, exec_t mode)
{
    char        *err_str;
    t_sh_cmd    *cmd;

    err_str = NULL;
    cmd = tree->command;
    if (sh_init_command(cmd, exec_ctx) || sh_check_command(cmd, exec_ctx))
        return;
    if (!sh_process_builtin(cmd, node_fd, exec_ctx, mode))
        return;
    if (access(cmd->executable, F_OK))
    {
        simulate_pid_child(127, exec_ctx);
        if (cmd->arguments && *cmd->arguments)
            err_str = *cmd->arguments;
        print_error_message(ERR_NOCMD, err_str);
        return;
    }
    sh_run_cmd(cmd, node_fd, exec_ctx);
}
