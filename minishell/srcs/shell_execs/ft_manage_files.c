#include "../../includes/minishell.h"

error_t     open_heredocs(t_sh_cmd *cmd)
{
    error_t     err;
    t_sh_redir  *tmp;
    char        *hd_file;

    err = ERR_NONE;
    tmp = cmd->redirects;
    while (tmp && cmd->heredoc_fd != -1)
    {
        if (tmp->mode == REDIR_HEREDOC)
        {
            hd_file = get_temp_file(".heredoc", 16);
            if (cmd->heredoc_fd > 2)
                close(cmd->heredoc_fd);
            cmd->heredoc_fd = get_heredoc(ft_strdup(tmp->target), hd_file);
            if (cmd->heredoc_fd == FILE_HDOC)
                return (ERR_HSTOP);
        }
        tmp = tmp->next;
    }
    return (cmd->heredoc_fd == FILE_ERR);
}

error_t     check_file(t_sh_cmd *cmd, char **file)
{
    char    **files;
    char    *var;

    var = ft_strdup(*file);
    replace_env_vars(*cmd->environment, file, QT_NONE);
    if (verify_wildcar(*file, QT_NONE))
        expand_wildcars(file);
    files = ft_split(*file, ' ');
    if (array_len(files) > 1)
    {
        print_error_message(ERR_AMB, var);
        free(var);
        free(*file);
        free_str_array((void **)files);
        return (ERR_AMB);
    }
    free(var);
    free_str_array((void **) files);
    return (ERR_NONE);
}

error_t     open_file_fd(t_sh_cmd *cmd, char *file, int mode)
{
    int     *fd;

    if (check_file(cmd, &file))
        return (ERR_AMB);
    if (mode == OPEN_READ)
        fd = &(cmd->input_fd);
    else
        fd = &(cmd->outfile);
    if (*fd > 2)
        close(*fd);
    if (mode != OPEN_READ && *fd != FILE_ERR)
        *fd = open(file, mode, 0644);
    else if (*fd != -1)
        *fd = open(file, mode);
    if (*fd == -1)
    {
        if (errno == ENFILE)
            print_error_message(ERR_FD, file);
        else
            print_error_message(ERR_NOENT, file);
        free(file);
        return (ERR_FD);
    }
    free(file);
    return (ERR_NONE);
}

error_t     open_outputs(t_sh_cmd *cmd)
{
    t_sh_redir      *tmp;
    error_t         op;

    tmp = cmd->redirects;
    op = ERR_NONE;
    while (tmp && cmd->outfile != FILE_ERR && op == ERR_NONE)
    {
        if (tmp->mode == REDIR_IN && access(tmp->target, R_OK))
            break;
        if (tmp->mode == REDIR_OUT)
            op = open_file_fd(cmd, ft_strdup(tmp->target), OPEN_CREATE);
        else if (tmp->mode == REDIR_APPEND)
            op = open_file_fd(cmd, ft_strdup(tmp->target), OPEN_APPEND);
        if (cmd->outfile != FILE_ERR)
            tmp = tmp->next;
    }
    if (op == ERR_FD || op == ERR_AMB)
        return (op);
    return (cmd->outfile == FILE_ERR && access(tmp->target, R_OK));
}

error_t     open_inputs(t_sh_cmd *cmd, int *hd_last)
{
    t_sh_redir  *tmp;
    error_t     op;

    if (!cmd->redirects)
        return (ERR_NONE);
    tmp = cmd->redirect;
    op = ERR_NONE;
    *hd_last = 0;
    while (tmp && cmd->input_fd != FILE_ERR && op == ERR_NONE)
    {
        if (tmp->mode == REDIR_IN)
        {
            *hd_last = 0;
            op = open_file_fd(cmd, ft_strdup(tmp->target), OPEN_READ);
        }
        if (tmp->mode != REDIR_OUT && tmp->mode != REDIR_APPEND)
            *hd_last |= (tmp->mode == REDIR_HEREDOC);
        tmp = tmp->next;
    }
    if (op == ERR_FD || op == ERR_AMB)
        return (op);
    return (cmd->input_fd == FILE_ERR);
}
