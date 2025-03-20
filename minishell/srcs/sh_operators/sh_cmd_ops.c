#include "../../includes/minishell.h"

char    **quoted_split(char *s, char *sep)
{
    t_qstate    state;
    char    **result;
    char    *ptr;
    char    *segment;

    result = NULL;
    state = QT_NONE;
    if (!s || !sep || !*s)
        return (str_array_create(ft_strdup("")));
    ptr = s;
    while (*s && *ptr)
    {
        ptr = s;
        while (*ptr && (!ft_strchr(sep, *ptr) || state != QT_NONE))
            update_quote_status(*(ptr++), &state);
        segment = ft_strndup(s, ptr - s);
        str_append(&result, segment);
        s = ptr;
        while (*s && ft_strchr(sep, *s))
            s++;
    }
    return (result);
}

void    update_arguments(t_sh_cmd *cmd)
{
    char        **new_args;
    char        **raw;
    char        **tmp;

    tmp = cmd->arguments;
    new_args = NULL;
    while (tmp && *tmp)
    {
        if (ft_strchr(*tmp, '$'))
        {
            replace_env_vars(*cmd->environment, tmp, QT_NONE);
            if (**tmp)
            {
                raw = ft_split(*tmp, ' ');
                str_tab_join(&new_args, raw);
            }
            tmp++;
            continue;
        }
        if (ft_strncmp(*cmd->arguments, "export", 7))
            remove_quotes(tmp, QT_NONE);
        str_append(&new_args, ft_strdup(*(tmp++)));
    }
    free_str_array((void **)cmd->arguments);
    cmd->arguments = new_args;
}

void    update_command_path(t_sh_cmd *cmd)
{
    free(cmd->executable);
    cmd->executable = NULL;
    if (cmd->arguments && *cmd->arguments)
        cmd->executable = sh_get_path(*cmd->arguments, *(cmd->environment));
}

error_t     prepare_command(t_sh_cmd *cmd)
{
    char    **tmp;

    update_arguments(cmd);
    tmp = cmd->arguments;
    while (tmp && *tmp)
    {
        if (verify_wildcard(*tmp, QT_NONE))
            expand_wildcards(tmp++);
        else
            remove_quotes(tmp++, QT_NONE);
    }
    update_command_path(cmd);
    if (!cmd->executable && !cmd->redirects)
        return (ERR_NOCMD);
    return (ERR_NONE);
}

error_t     handle_heredocs(t_sh_node *nd, int *nd, int *hd)
{
    t_error     err;

    if (!nd)
        return (ERR_GEN);
    err = (ERR_NONE);
    if (*hd)
        return (ERR_HSTOP);
    if (!nd->command)
    {
        err |= handle_heredocs(nd->left, hd);
        err |= handle_heredocs(nd->right, hd);
        return (err);
    }
    err = open_heredocs(nd->command);
    return (err);
}