/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmd_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:35 by jnovack           #+#    #+#             */
/*   Updated: 2025/06/02 12:01:56 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_refresh_args(t_sh_cmd *cmd)
{
	char			**new_args;
	char			**raw;
	char			**tmp;
	t_quote_state	qt;

	new_args = NULL;
	tmp = cmd->arguments;
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
			ft_strapp(&new_args, ft_strdup(*tmp));
		tmp++;
	}
	ft_free_tab((void **)cmd->arguments);
	cmd->arguments = new_args;
}

void	sh_refresh_executable(t_sh_cmd *cmd)
{
	free(cmd->executable);
	cmd->executable = NULL;
	if (cmd->arguments && *cmd->arguments)
		cmd->executable = sh_find_path(*cmd->arguments, *(cmd->environment));
}

t_error_t	sh_prepare_cmd(t_sh_cmd *cmd)
{
	char	**tmp;

	sh_refresh_args(cmd);
	tmp = cmd->arguments;
	while (tmp && *tmp)
	{
		if (sh_contains_unquoted_wildcard(*tmp, QUOTE_NONE))
			sh_replace_wildcards(tmp);
		tmp++;
	}
	sh_refresh_executable(cmd);
	if (!cmd->executable && !cmd->redirects)
		return (ERR_NO_COMMAND);
	return (ERR_NONE);
}

t_error_t	sh_traverse_heredocs(t_sh_node *node, int *heredoc)
{
	t_error_t	error;

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
	return (sh_heredoc_init(node->cmd));
}
