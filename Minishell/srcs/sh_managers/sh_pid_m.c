/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pid_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:16 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 14:21:13 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sh_pid	*sh_init_pid(pid_t pid)
{
	t_sh_pid	*new_pid;

	new_pid = malloc(sizeof(t_sh_pid));
	if (!new_pid)
		return (NULL);
	new_pid->pid = pid;
	new_pid->next = NULL;
	return (new_pid);
}

void	sh_pid_push(t_sh_pid **head, t_sh_pid *top)
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

t_sh_pid	*sh_pid_pop(t_sh_pid **head)
{
	t_sh_pid	*tmp;

	if (!head || !*head)
		return (NULL);
	tmp = *head;
	*head = (*head)->next;
	tmp->next = NULL;
	return (tmp);
}

void	sh_delete_pid_list(t_sh_pid *pid_list)
{
	if (!pid_list)
		return ;
	sh_delete_pid_list(pid_list->next);
	free(pid_list);
}
