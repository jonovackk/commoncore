/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:54 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 15:48:23 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_shell_exit_status;

void	sh_create_fake_pid_child(int err_code, t_sh_exec *executor)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		return ;
	if (child == 0)
	{
		sh_tree_fd_cleanup(sh_command_tree_state(0, NULL));
		sh_fork_cleanup(executor);
		exit(err_code);
	}
	sh_pid_push(&(executor->running_procs), sh_init_pid(child));
}

void	sh_process_redirections(t_sh_cmd *cmd, int *node_fd)
{
	if (cmd->input_fd != STDIN_FILENO)
	{
		dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
	}
	if (node_fd[0] != STDIN_FILENO)
	{
		dup2(node_fd[0], STDIN_FILENO);
		close(node_fd[0]);
	}
	if (node_fd[1] != STDOUT_FILENO)
	{
		dup2(node_fd[1], STDOUT_FILENO);
		close(node_fd[1]);
	}
	sh_cmd_cleanup(cmd);
}

void	sh_process_command_exit(int exit_status)
{
	if (!WIFEXITED(exit_status) && WCOREDUMP(exit_status))
	{
		ft_dprintf(2, "Quit (core dumped)\n");
		g_shell_exit_status = 131;
	}
	if (WTERMSIG(exit_status) == SIGINT)
	{
		ft_dprintf(2, "\n");
		g_shell_exit_status = 130;
	}
}

void	sh_fork_cleanup(t_sh_exec *executor)
{
	if (!executor)
		return ;
	sh_cleanup_pipes(executor->active_pipes);
}
