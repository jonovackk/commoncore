/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_pipeline_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:09 by jnovack           #+#    #+#             */
/*   Updated: 2025/06/02 12:04:13 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_shell_exit_status;

void	sh_execute_command_multiplex(t_sh_node *node, int *node_fd,
		t_sh_exec *executor, t_exec_t execution_mode)
{
	if (!executor || !node || !node_fd)
		return ;
	if (node->token)
	{
		if (node->token->type & TOKEN_LOGICAL)
		{
			if (!ft_strncmp(node->token->content, "&&", 3))
				sh_and_exec(node, node_fd, executor, execution_mode);
			else
				sh_or_exec(node, node_fd, executor, execution_mode);
		}
		else
		{
			sh_execute_pipeline(node, node_fd, executor, execution_mode);
		}
	}
	else if (node->cmd)
	{
		sh_handle_command(node, node_fd, executor, execution_mode);
	}
}

void	sh_wait_pipeline_processes(t_sh_pid *initial_pid, t_sh_exec *executor,
		t_exec_t execution_mode)
{
	t_sh_pid	*waiting_process;
	int			process_exit_code;
	int			is_first_process;
	t_sh_pipe	*pipe_node;

	is_first_process = 0;
	pipe_node = sh_pipe_pop(&executor->active_pipes);
	while (pipe_node != NULL)
	{
		sh_delete_pipe(pipe_node);
		pipe_node = sh_pipe_pop(&executor->active_pipes);
	}
	sh_delete_pipe(sh_pipe_pop(&(executor->active_pipes)));
	while (execution_mode == EXEC_WAIT && executor
		&& executor->running_procs != initial_pid)
	{
		waiting_process = sh_pid_pop(&(executor->running_procs));
		waitpid(waiting_process->pid, &process_exit_code, 0);
		sh_process_command_exit(process_exit_code);
		if (!is_first_process++)
			g_shell_exit_status = WEXITSTATUS(process_exit_code);
		free(waiting_process);
	}
}

void	sh_execute_pipeline(t_sh_node *node, int *node_fd, t_sh_exec *executor,
		t_exec_t execution_mode)
{
	int			pipe_fd[2];
	t_sh_pid	*initial_pid;
	t_sh_pipe	*new_pipe;

	initial_pid = NULL;
	new_pipe = sh_init_pipe();
	if (execution_mode == EXEC_WAIT)
		initial_pid = executor->running_procs;
	if (!new_pipe || new_pipe->fds[0] == -1 || new_pipe->fds[1] == -1)
	{
		fprintf(stderr, "Error: Failed to create pipe.\n");
		return ;
	}
	pipe_fd[0] = node_fd[0];
	pipe_fd[1] = new_pipe->fds[1];
	sh_execute_command_multiplex(node->left, pipe_fd, executor, EXEC_PIPE);
	close(new_pipe->fds[1]);
	pipe_fd[0] = new_pipe->fds[0];
	pipe_fd[1] = node_fd[1];
	sh_execute_pipeline_right_branch(node, pipe_fd, executor);
	close(new_pipe->fds[0]);
	sh_delete_pipe(new_pipe);
	if (execution_mode == EXEC_WAIT)
		sh_wait_pipeline_processes(initial_pid, executor, execution_mode);
}

void	sh_and_exec(t_sh_node *node, int *node_fd, t_sh_exec *ex, t_exec_t mode)
{
	pid_t	child;
	int		err_code;

	err_code = 0;
	if (mode == EXEC_PIPE)
	{
		child = fork();
		if (child == -1)
			return ;
		if (child == 0)
		{
			err_code = sh_execute_logical_and(node, node_fd, ex);
			sh_fork_cleanup(ex);
			exit(err_code);
		}
		sh_pid_push(&(ex->running_procs), sh_init_pid(child));
	}
	else
	{
		sh_execute_logical_and(node, node_fd, ex);
	}
}

void	sh_or_exec(t_sh_node *node, int *node_fd, t_sh_exec *ex, t_exec_t mode)
{
	pid_t	child;
	int		err_code;

	err_code = 0;
	if (mode == EXEC_PIPE)
	{
		child = fork();
		if (child == -1)
			return ;
		if (child == 0)
		{
			err_code = sh_execute_logical_or(node, node_fd, ex);
			sh_fork_cleanup(ex);
			exit(err_code);
		}
		sh_pid_push(&(ex->running_procs), sh_init_pid(child));
	}
	else
	{
		sh_execute_logical_or(node, node_fd, ex);
	}
}
