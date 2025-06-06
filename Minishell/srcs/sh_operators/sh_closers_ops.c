/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_closers_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:32 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 14:54:59 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_close_multiple_fd(int count, int fd, ...)
{
	va_list	files;
	int		current_fd;
	int		i;

	i = 0;
	close(fd);
	va_start(files, fd);
	while (i++ < count)
	{
		current_fd = va_arg(files, int);
		if (current_fd >= 0)
			close(current_fd);
	}
	va_end(files);
}

void	sh_cmd_cleanup(t_sh_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->input_fd > STDERR_FILENO)
		close(cmd->input_fd);
	if (cmd->output_fd > STDERR_FILENO)
		close(cmd->output_fd);
	if (cmd->heredoc_fd > STDERR_FILENO)
		close(cmd->heredoc_fd);
}

void	sh_tree_fd_cleanup(t_sh_node *tree)
{
	if (!tree)
		return ;
	if (tree->left)
		sh_tree_fd_cleanup(tree->left);
	if (tree->right)
		sh_tree_fd_cleanup(tree->right);
	if (tree->cmd)
		sh_cmd_cleanup(tree->cmd);
}

void	sh_exec_release(t_sh_exec *executor)
{
	t_sh_pipe	*current_pipe;
	t_sh_pid	*current_pid;

	if (!executor)
		return ;
	while (executor->active_pipes)
	{
		current_pipe = sh_pipe_pop(&(executor->active_pipes));
		if (current_pipe->fds[0] > STDERR_FILENO)
			close(current_pipe->fds[0]);
		if (current_pipe->fds[1] > STDERR_FILENO)
			close(current_pipe->fds[1]);
		free(current_pipe);
	}
	while (executor->running_procs)
	{
		current_pid = sh_pid_pop(&(executor->running_procs));
		free(current_pid);
	}
}

void	sh_cleanup_pipes(t_sh_pipe *pipes)
{
	t_sh_pipe	*tmp;

	while (pipes)
	{
		if (pipes->fds[0] > STDERR_FILENO)
			close(pipes->fds[0]);
		if (pipes->fds[1] > STDERR_FILENO)
			close(pipes->fds[1]);
		tmp = pipes;
		pipes = pipes->next;
		free(tmp);
	}
}
