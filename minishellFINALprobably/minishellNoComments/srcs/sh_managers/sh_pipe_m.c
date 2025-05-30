/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipe_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:20 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 14:21:31 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sh_pipe	*sh_init_pipe(void)
{
	t_sh_pipe	*new_pipe;

	new_pipe = malloc(sizeof(t_sh_pipe));
	if (!new_pipe)
		return (NULL);
	new_pipe->fds[0] = -1;
	new_pipe->fds[1] = -1;
	if (pipe(new_pipe->fds) == -1)
	{
		free(new_pipe);
		return (NULL);
	}
	new_pipe->next = NULL;
	return (new_pipe);
}

void	sh_pipe_push(t_sh_pipe **head, t_sh_pipe *top)
{
	if (!head || !top)
		return ;
	if (!*head)
	{
		*head = top;
		return ;
	}
	top->next = *head;
	*head = top;
}

t_sh_pipe	*sh_pipe_pop(t_sh_pipe **head)
{
	t_sh_pipe	*tmp;

	if (!head || !*head)
		return (NULL);
	tmp = *head;
	*head = (*head)->next;
	tmp->next = NULL;
	return (tmp);
}

void	sh_delete_pipe(t_sh_pipe *pipe_node)
{
	if (!pipe_node)
		return ;
	if (pipe_node->fds[0] > 2)
		close(pipe_node->fds[0]);
	if (pipe_node->fds[1] > 2)
		close(pipe_node->fds[1]);
	free(pipe_node);
}
