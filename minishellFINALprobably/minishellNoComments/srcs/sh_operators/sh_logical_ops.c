/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_logical_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:02 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 15:51:12 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_shell_exit_status;

int	sh_wait_logical_operation(t_sh_exec *executor)
{
	t_sh_pid	*process_to_wait;
	int			exit_code;

	process_to_wait = sh_pid_pop(&(executor->running_procs));
	exit_code = 0;
	if (process_to_wait)
	{
		sh_cleanup_pipes(executor->active_pipes);
		waitpid(process_to_wait->pid, &exit_code, 0);
		sh_process_command_exit(exit_code);
		exit_code = WEXITSTATUS(exit_code);
	}
	else
		exit_code = g_shell_exit_status;
	free(process_to_wait);
	return (exit_code);
}

int	sh_execute_logical_and(t_sh_node *tree, int *node_fd, t_sh_exec *executor)
{
	int	exit_code;

	if (node_fd[0] != STDERR_FILENO)
		dup2(node_fd[0], STDIN_FILENO);
	sh_execute_command_multiplex(tree->left, node_fd, executor, EXEC_WAIT);
	exit_code = sh_wait_logical_operation(executor);
	g_shell_exit_status = exit_code;
	if (exit_code == ERR_NONE)
	{
		sh_execute_command_multiplex(tree->right, node_fd, executor, EXEC_WAIT);
		g_shell_exit_status = sh_wait_logical_operation(executor);
	}
	return (g_shell_exit_status);
}

int	sh_execute_logical_or(t_sh_node *tree, int *node_fd, t_sh_exec *executor)
{
	int		exit_code;

	if (node_fd[0] != STDIN_FILENO)
		dup2(node_fd[0], STDIN_FILENO);
	sh_execute_command_multiplex(tree->left, node_fd, executor, EXEC_WAIT);
	exit_code = sh_wait_logical_operation(executor);
	g_shell_exit_status = exit_code;
	if (exit_code != ERR_NONE)
	{
		sh_execute_command_multiplex(tree->right, node_fd, executor, EXEC_WAIT);
		g_shell_exit_status = sh_wait_logical_operation(executor);
	}
	return (g_shell_exit_status);
}
