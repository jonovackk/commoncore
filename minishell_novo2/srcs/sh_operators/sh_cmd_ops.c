/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:35 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/13 14:03:42 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * 1) tokenize_quoted: separa por SEP (ex: espaço) mas IGNORA separadores
 *    que estiverem dentro de um par de aspas.
 */
char **sh_tokenize_quoted(char *s, char *sep)
{
    char          **result = NULL;
    char           *start;
    t_quote_state   state;
    size_t          len;

    if (!s || !sep || !*s)
        return (ft_strtab(ft_strdup("")));
    while (*s)
    {
        /* pula separadores fora de aspas */
        while (*s && ft_strchr(sep, *s))
            s++;
        if (!*s)
            break;

        start = s;
        state = QUOTE_NONE;
        /* anda até encontrar sep FORA de aspas */
        while (*s && (state != QUOTE_NONE || !ft_strchr(sep, *s)))
        {
            sh_update_quote_state(*s, &state);
            s++;
        }
        len = s - start;
        if (len > 0)
            ft_strapp(&result, ft_strndup(start, len));
    }
    return (result);
}

/*
 * 2) sh_refresh_args: já detecta corretamente QUOTE_SINGLE/DOUBLE
 *    e só remove aspas externas UMA VEZ.
 */
void sh_refresh_args(t_sh_cmd *cmd)
{
    char           **new_args = NULL;
    char           **raw;
    char           **tmp = cmd->arguments;
    t_quote_state   qt;

    while (tmp && *tmp)
    {
        qt = detect_quote_type(*tmp);

        if (ft_strchr(*tmp, '$') && qt != QUOTE_SINGLE)
            sh_replace_env_vars(*cmd->environment, tmp, qt);

        if (qt != QUOTE_NONE)
            sh_rmv_quotes(tmp, qt);

        if (qt == QUOTE_NONE)
        {
            raw = ft_split(*tmp, ' ');
            ft_str_tabjoin(&new_args, raw);
        }
        else
        {
            ft_strapp(&new_args, ft_strdup(*tmp));
        }
        tmp++;
    }
    ft_free_tab((void **)cmd->arguments);
    cmd->arguments = new_args;
}

/*
 * 3) sh_refresh_executable: sem alterações
 */
void sh_refresh_executable(t_sh_cmd *cmd)
{
    free(cmd->executable);
    cmd->executable = NULL;
    if (cmd->arguments && *cmd->arguments)
        cmd->executable = sh_find_path(*cmd->arguments, *(cmd->environment));
}

/*
 * 4) sh_prepare_cmd: substitui o else que removia aspas sem checar tipo
 */
error_t sh_prepare_cmd(t_sh_cmd *cmd)
{
    char           **tmp;

    sh_refresh_args(cmd);
    tmp = cmd->arguments;
    while (tmp && *tmp)
    {
        if (sh_contains_unquoted_wildcard(*tmp, QUOTE_NONE))
            sh_replace_wildcards(tmp);
        // removido: else sh_rmv_quotes(tmp++, …)
        tmp++;
    }
    sh_refresh_executable(cmd);
    if (!cmd->executable && !cmd->redirects)
        return (ERR_NO_COMMAND);
    return (ERR_NONE);
}


/*
 * 5) sh_traverse_heredocs: sem alterações
 */
error_t sh_traverse_heredocs(t_sh_node *node, int *heredoc)
{
    error_t error;

    if (!node)
        return (ERR_ERRORS);
    error = ERR_NONE;
    if (*heredoc)
        return (ERR_HEREDOC_ABORTED);
    if (!node->cmd)
    {
        error |= sh_traverse_heredocs(node->left, heredoc);
        error |= sh_traverse_heredocs(node->right, heredoc);
        return (error);
    }
    return sh_heredoc_init(node->cmd);
}
