#include "../../includes/minishell.h"

error_t     sh_heredoc_init(t_sh_cmd *cmd)
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
            cmd->heredoc_fd = sh_create_heredoc(ft_strdup(tmp->target), hd_file);
            if (cmd->heredoc_fd == FILE_HEREDOC_TEMP)
                return (ERR_HEREDOC_ABORTED);
        }
        tmp = tmp->next;
    }
    return (cmd->heredoc_fd == FILE_ERROR);
}

error_t     sh_line_expand(t_sh_cmd *cmd, char **file)
{
    char    **files;
    char    *var;

    var = ft_strdup(*file);
    sh_replace_env_vars(*cmd->environment, file, QUOTE_NONE);
    if (sh_contains_unquoted_wildcard(*file, QUOTE_NONE))
        sh_replace_wildcards(file);
    files = ft_split(*file, ' ');
    if (array_len(files) > 1)
    {
        sh_display_error(ERR_AMBIGUOUS_REDIRECT, var);
        free(var);
        free(*file);
        free_str_array((void **)files);
        return (ERR_AMBIGUOUS_REDIRECT);
    }
    free(var);
    free_str_array((void **) files);
    return (ERR_NONE);
}

error_t     sh_heredoc_write(t_sh_cmd *cmd, char *file, int mode)
{
    int     *fd;

    if (sh_line_expand(cmd, &file))
        return (ERR_AMBIGUOUS_REDIRECT);
    if (mode == OPEN_READ)
        fd = &(cmd->input_fd);
    else
        fd = &(cmd->outfile);
    if (*fd > 2)
        close(*fd);
    if (mode != OPEN_READ && *fd != FILE_ERROR)
        *fd = open(file, mode, 0644);
    else if (*fd != -1)
        *fd = open(file, mode);
    if (*fd == -1)
    {
        if (errno == ENFILE)
            sh_display_error(ERR_FD_LIMIT, file);
        else
            sh_display_error(ERR_NO_ENTRY, file);
        free(file);
        return (ERR_FD_LIMIT);
    }
    free(file);
    return (ERR_NONE);
}

error_t     sh_output_load(t_sh_cmd *cmd)
{
    t_sh_redir      *tmp;
    error_t         op;

    tmp = cmd->redirects;
    op = ERR_NONE;
    while (tmp && cmd->outfile != FILE_ERROR && op == ERR_NONE)
    {
        if (tmp->mode == REDIR_INPUT && access(tmp->target, R_OK))
            break;
        if (tmp->mode == REDIR_OUTPUT)
            op = sh_heredoc_write(cmd, ft_strdup(tmp->target), OPEN_CREATE);
        else if (tmp->mode == REDIR_APPEND)
            op = sh_heredoc_write(cmd, ft_strdup(tmp->target), OPEN_APPEND);
        if (cmd->outfile != FILE_ERROR)
            tmp = tmp->next;
    }
    if (op == ERR_FD_LIMIT || op == ERR_AMBIGUOUS_REDIRECT)
        return (op);
    return (cmd->outfile == FILE_ERROR && access(tmp->target, R_OK));
}

error_t     sh_input_load(t_sh_cmd *cmd, int *hd_last)
{
    t_sh_redir  *tmp;
    error_t     op;

    if (!cmd->redirects)
        return (ERR_NONE);
    tmp = cmd->redirect;
    op = ERR_NONE;
    *hd_last = 0;
    while (tmp && cmd->input_fd != FILE_ERROR && op == ERR_NONE)
    {
        if (tmp->mode == REDIR_INPUT)
        {
            *hd_last = 0;
            op = sh_heredoc_write(cmd, ft_strdup(tmp->target), OPEN_READ);
        }
        if (tmp->mode != REDIR_OUTPUT && tmp->mode != REDIR_APPEND)
            *hd_last |= (tmp->mode == REDIR_HEREDOC);
        tmp = tmp->next;
    }
    if (op == ERR_FD_LIMIT || op == ERR_AMBIGUOUS_REDIRECT)
        return (op);
    return (cmd->input_fd == FILE_ERROR);
}
