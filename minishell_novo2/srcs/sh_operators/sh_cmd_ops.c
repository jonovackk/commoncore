/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:35 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/13 11:20:36 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void sh_refresh_args(t_sh_cmd *cmd)
{
    char **new_args = NULL;
    char **raw;
    char **tmp = cmd->arguments;
    t_quote_state quote_type;

    while (tmp && *tmp)
    {
        quote_type = detect_quote_type(*tmp);

        // Substituição de variáveis, se permitido
        if (ft_strchr(*tmp, '$') && quote_type != QUOTE_SINGLE)
        {
            sh_replace_env_vars(*cmd->environment, tmp, quote_type);
        }

        // Remoção de aspas externas (apenas uma vez!)
        if (quote_type != QUOTE_NONE)
        {
            printf("Removendo aspas de: [%s]\n", *tmp);
            sh_rmv_quotes(tmp, quote_type);
        }

        // Se não há aspas, separar argumentos por espaço
        if (quote_type == QUOTE_NONE)
        {
            raw = ft_split(*tmp, ' ');
            ft_str_tabjoin(&new_args, raw);
        }
        else
        {
            // Copiar argumento completo
            ft_strapp(&new_args, ft_strdup(*tmp));
        }

        tmp++;
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