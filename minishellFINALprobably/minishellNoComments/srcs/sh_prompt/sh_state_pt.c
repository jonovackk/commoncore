/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_state_pt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:24 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 15:56:00 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*sh_double_quote_state(char *addr, int type)
{
	static char	*sh_dq_line = NULL;
	static int	sh_dq_fd = -1;

	if (!sh_dq_line || (addr && type == 0))
		sh_dq_line = addr;
	if (sh_dq_fd == -1 || (addr && type == 0))
		sh_dq_fd = *(int *)addr;
	if (type == 0)
		return (sh_dq_line);
	return ((char *)&sh_dq_fd);
}

char	*sh_heredoc_state(char *addr, int type)
{
	static char	*sh_hd_filename = NULL;
	static char	*sh_hd_delimiter = NULL;
	static int	sh_hd_fd = -1;

	if (!sh_hd_filename || (addr && type == 0))
		sh_hd_filename = addr;
	else if ((!sh_hd_delimiter || (addr && type == 1)))
		sh_hd_delimiter = addr;
	else if ((sh_hd_fd = -1 || (addr && type == 2)))
		sh_hd_fd = *(int *)addr;
	if (type == 0)
		return (sh_hd_filename);
	if (type == 1)
		return (sh_hd_delimiter);
	return ((char *)&sh_hd_fd);
}

t_sh_node	*sh_command_tree_state(int reset, t_sh_node *root)
{
	static t_sh_node	*sh_command_tree_state = NULL;

	(void)reset;
	if (root)
		sh_command_tree_state = root;
	return (sh_command_tree_state);
}
