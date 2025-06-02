/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_cmd_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:07:38 by jnovack           #+#    #+#             */
/*   Updated: 2025/06/02 12:02:27 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_setup_input(t_sh_cmd *cmd, int last_hd)
{
	if (last_hd)
	{
		if (cmd->input_fd != STDIN_FILENO)
			close(cmd->input_fd);
		cmd->input_fd = cmd->heredoc_fd;
	}
	else
	{
		if (cmd->heredoc_fd > 2)
			close(cmd->heredoc_fd);
	}
}

void	sh_run_cmd(t_sh_cmd *cmd, int *node_fd, t_sh_exec *exec_ctx)
{
	char	**env_vars;
	pid_t	pid;

	env_vars = sh_create_env_array(*(cmd->environment), 0);
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		sh_setup_child_io(cmd, node_fd);
		sh_execute_child(cmd, env_vars, exec_ctx);
	}
	else
	{
		sh_cleanup_parent(cmd, node_fd);
		sh_pid_push(&(exec_ctx->running_procs), sh_init_pid(pid));
	}
}

t_error_t	sh_init_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx)
{
	int	last_hd;

	last_hd = 0;
	if (sh_prepare_cmd(cmd))
	{
		sh_create_fake_pid_child(0, exec_ctx);
		return (ERR_NO_COMMAND);
	}
	if (sh_output_load(cmd) || sh_input_load(cmd, &last_hd))
	{
		sh_create_fake_pid_child(1, exec_ctx);
		return (ERR_FAIL_GENERAL);
	}
	sh_setup_input(cmd, last_hd);
	if (!cmd->executable && cmd->redirects)
	{
		sh_create_fake_pid_child(0, exec_ctx);
		return (ERR_FAIL_GENERAL);
	}
	return (ERR_NONE);
}

t_error_t	sh_check_command(t_sh_cmd *cmd, t_sh_exec *exec_ctx)
{
	struct stat	s_buf;

	if (access(cmd->executable, F_OK))
		return (ERR_NONE);
	stat(cmd->executable, &s_buf);
	if (!S_ISREG(s_buf.st_mode))
	{
		if (S_ISFIFO(s_buf.st_mode))
			sh_display_error(ERR_NO_PERMISS, cmd->executable);
		else if (S_ISDIR(s_buf.st_mode))
			sh_display_error(ERR_IS_DIRECTORY, cmd->executable);
		sh_create_fake_pid_child(126, exec_ctx);
		return (ERR_FAIL_GENERAL);
	}
	return (ERR_NONE);
}

void	sh_handle_command(t_sh_node *tree, int *node_fd, t_sh_exec *exec_ctx,
		t_exec_t mode)
{
	char		*err_str;
	t_sh_cmd	*command;

	err_str = NULL;
	command = tree->cmd;
	if (sh_init_command(command, exec_ctx) || sh_check_command(command,
			exec_ctx))
		return ;
	if (!sh_process_builtin(command, node_fd, exec_ctx, mode))
		return ;
	if (access(command->executable, F_OK))
	{
		sh_create_fake_pid_child(127, exec_ctx);
		if (command->arguments && *command->arguments)
			err_str = *command->arguments;
		sh_display_error(ERR_NO_COMMAND, err_str);
		return ;
	}
	sh_run_cmd(command, node_fd, exec_ctx);
}
