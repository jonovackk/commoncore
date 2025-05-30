/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipeline_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:36:47 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 16:37:06 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_execute_pipeline_right_branch(t_sh_node *node, int *pipe_fd,
		t_sh_exec *executor)
{
	if (node->right && node->right->token
		&& node->right->token->type == TOKEN_PIPE)
	{
		fprintf(stderr, "Recursing into nested pipeline\n");
		sh_execute_pipeline(node->right, pipe_fd, executor, EXEC_PIPE);
	}
	else
	{
		sh_execute_command_multiplex(node->right, pipe_fd, executor, EXEC_PIPE);
	}
}
