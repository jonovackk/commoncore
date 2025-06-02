/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_run_cmd_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:13:53 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 16:16:55 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_setup_child_io(t_sh_cmd *cmd, int *node_fd)
{
	sh_dup_input(cmd, node_fd);
	sh_dup_output(cmd, node_fd);
}

void	sh_dup_input(t_sh_cmd *cmd, int *node_fd)
{
	if (cmd->heredoc_fd >= 0)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
			perror("dup2 heredoc_fd");
		close(cmd->heredoc_fd);
		node_fd[0] = -1;
	}
	else if (cmd->input_fd >= 0 && cmd->input_fd != STDIN_FILENO)
	{
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
			perror("dup2 input_fd");
		close(cmd->input_fd);
	}
	else if (node_fd[0] >= 0 && node_fd[0] != STDIN_FILENO)
	{
		if (dup2(node_fd[0], STDIN_FILENO) == -1)
			perror("dup2 node_fd[0]");
		close(node_fd[0]);
	}
}

void	sh_dup_output(t_sh_cmd *cmd, int *node_fd)
{
	if (cmd->output_fd >= 0 && cmd->output_fd != STDOUT_FILENO)
	{
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
			perror("dup2 output_fd");
		close(cmd->output_fd);
	}
	else if (node_fd[1] >= 0 && node_fd[1] != STDOUT_FILENO)
	{
		if (dup2(node_fd[1], STDOUT_FILENO) == -1)
			perror("dup2 node_fd[1]");
		close(node_fd[1]);
	}
}

void	sh_execute_child(t_sh_cmd *cmd, char **env_vars, t_sh_exec *exec_ctx)
{
	sh_cleanup_pipes(exec_ctx->active_pipes);
	execve(cmd->executable, cmd->arguments, env_vars);
	perror("execve");
	exit(127);
}

void	sh_cleanup_parent(t_sh_cmd *cmd, int *node_fd)
{
	if (cmd->input_fd >= 0 && cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	if (cmd->output_fd >= 0 && cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	if (node_fd[0] >= 0 && node_fd[0] != STDIN_FILENO)
		close(node_fd[0]);
	if (node_fd[1] >= 0 && node_fd[1] != STDOUT_FILENO)
		close(node_fd[1]);
	if (cmd->heredoc_fd >= 0)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	sh_cmd_cleanup(cmd);
}
