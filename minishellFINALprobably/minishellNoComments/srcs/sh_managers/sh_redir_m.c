/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_redir_m.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:23 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 14:21:47 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sh_redir	*sh_new_redir(t_sh_token *tmp)
{
	t_sh_redir	*new_redir;

	new_redir = malloc(sizeof(t_sh_redir));
	if (!new_redir)
		return (NULL);
	if (!ft_strncmp(tmp->content, ">>", 3))
		new_redir->mode = REDIR_APPEND;
	else if (!ft_strncmp(tmp->content, "<<", 3))
		new_redir->mode = REDIR_HEREDOC;
	else if (!ft_strncmp(tmp->content, ">", 2))
		new_redir->mode = REDIR_OUTPUT;
	else if (!ft_strncmp(tmp->content, "<", 2))
		new_redir->mode = REDIR_INPUT;
	new_redir->target = ft_strdup(tmp->next->content);
	sh_rmv_quotes(&(new_redir->target), QUOTE_NONE);
	new_redir->next = NULL;
	return (new_redir);
}

void	sh_add_redir(t_sh_redir **redirs, t_sh_redir *next)
{
	t_sh_redir	*tmp;

	if (!redirs)
		return ;
	if (!*redirs)
	{
		*redirs = next;
		return ;
	}
	tmp = *redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = next;
}

void	sh_clear_redir_list(t_sh_redir *redir)
{
	if (!redir)
		return ;
	sh_clear_redir_list(redir->next);
	free(redir->target);
	free(redir);
}
