#include "../../includes/minishell.h"

char    **sh_tokenize_quoted(char *s, char *sep)
{
    t_quote_state    state;
    char    **result;
    char    *ptr;
    char    *segment;

    result = NULL;
    state = QUOTE_NONE;
    if (!s || !sep || !*s)
        return (ft_strtab(ft_strdup("")));
    ptr = s;
    while (*s && *ptr)
    {
        ptr = s;
        while (*ptr && (!ft_strchr(sep, *ptr) || state != QUOTE_NONE))
            sh_update_quote_state(*(ptr++), &state);
        segment = ft_strndup(s, ptr - s);
        ft_strapp(&result, segment);
        s = ptr;
        while (*s && ft_strchr(sep, *s))
            s++;
    }
    return (result);
}

void    sh_refresh_args(t_sh_cmd *cmd)
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
            sh_replace_env_vars(*cmd->environment, tmp, QUOTE_NONE);
            if (**tmp)
            {
                raw = ft_split(*tmp, ' ');
                ft_str_tabjoin(&new_args, raw);
            }
            tmp++;
            continue;
        }
        if (ft_strncmp(*cmd->arguments, "export", 7))
        sh_rmv_quotes(tmp, QUOTE_NONE);
        ft_strapp(&new_args, ft_strdup(*(tmp++)));
    }
    ft_free_tab((void **)cmd->arguments);
    cmd->arguments = new_args;
}

void    sh_refresh_executable(t_sh_cmd *cmd)
{
    free(cmd->executable);
    cmd->executable = NULL;
    if (cmd->arguments && *cmd->arguments)
        cmd->executable = sh_find_path(*cmd->arguments, *(cmd->environment));
}

error_t     sh_prepare_cmd(t_sh_cmd *cmd)
{
    char    **tmp;

    sh_refresh_args(cmd);
    tmp = cmd->arguments;
    while (tmp && *tmp)
    {
        if (sh_contains_unquoted_wildcard(*tmp, QUOTE_NONE))
            sh_replace_wildcards(tmp++);
        else
        sh_rmv_quotes(tmp++, QUOTE_NONE);
    }
    sh_refresh_executable(cmd);
    if (!cmd->executable && !cmd->redirects)
        return (ERR_NO_COMMAND);
    return (ERR_NONE);
}

error_t     sh_traverse_heredocs(t_sh_node *node, int *heredoc)
{
    error_t     error;

    if (!node)
        return (ERR_ERRORS);
    error = (ERR_NONE);
    if (*heredoc)
        return (ERR_HEREDOC_ABORTED);
    if (!node->cmd)
    {
        error |= sh_traverse_heredocs(node->left, heredoc);
        error |= sh_traverse_heredocs(node->right, heredoc);
        return (error);
    }
    error = sh_heredoc_init(node->cmd);
    return (error);
}