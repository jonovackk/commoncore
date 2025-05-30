/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_handler_ops.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:49:03 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 16:32:11 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_shell_exit_status;

void	sh_execute_builtin_piped(int (*builtin_func)(t_sh_cmd *), t_sh_cmd *cmd,
		t_sh_exec *exec_ctx)
{
	pid_t	child;
	int		ret;

	child = fork();
	if (child < 0)
		return ;
	if (child == 0)
	{
		ret = builtin_func(cmd);
		sh_cleanup_pipes(exec_ctx->active_pipes);
		sh_tree_fd_cleanup(sh_command_tree_state(0, NULL));
		sh_exec_release(exec_ctx);
		free(exec_ctx);
		exit(ret);
	}
	sh_cmd_cleanup(cmd);
	sh_pid_push(&(exec_ctx->running_procs), sh_init_pid(child));
}

void	sh_validate_builtin_direct(int (*builtin_func)(t_sh_cmd *),
		t_sh_cmd *cmd, t_sh_exec *exec_ctx)
{
	int	err_code;

	if (builtin_func == &sh_execute_exit && ft_tab_len(cmd->arguments) <= 2)
	{
		sh_tree_fd_cleanup(sh_command_tree_state(0, NULL));
		sh_exec_release(exec_ctx);
		free(exec_ctx);
		ft_dprintf(2, "exit\n");
	}
	err_code = builtin_func(cmd);
	sh_create_fake_pid_child(err_code, exec_ctx);
	sh_cmd_cleanup(cmd);
}

error_t	sh_validate_builtin_flags(t_sh_cmd *cmd)
{
	char	**tmp;

	if (!cmd || !cmd->arguments || !*cmd->arguments)
		return (ERR_NONE);
	tmp = cmd->arguments;
	if (!ft_strncmp(*tmp, "echo", 5))
		return (ERR_NONE);
	tmp++;
	if (!ft_strncmp(*(tmp - 1), "cd", 3) && *tmp && !ft_strncmp(*tmp, "-", 2))
		return (ERR_NONE);
	while (*tmp && **tmp != '-')
		tmp++;
	if (*tmp)
	{
		sh_display_error(ERR_INVALID_OPTION, *tmp);
		g_shell_exit_status = 156;
		return (ERR_INVALID_OPTION);
	}
	return (ERR_NONE);
}
error_t	sh_process_builtin(t_sh_cmd *cmd, int *fd, t_sh_exec *exec_ctx,
		exec_t mode)
{
	int			index;
	static int (*builtins[7])(t_sh_cmd *) = {&sh_execute_cd, &sh_execute_pwd,
		&sh_echo_execute, &sh_execute_env, &sh_execute_export,
		&sh_execute_unset, &sh_execute_exit};

	index = sh_get_builtin_index(cmd);
	if (index == -1)
		return (ERR_ERRORS);
	if (cmd->input_fd == STDIN_FILENO && fd[0] != STDERR_FILENO)
		cmd->input_fd = fd[0];
	if (cmd->output_fd == STDOUT_FILENO && fd[1] != STDERR_FILENO)
		cmd->output_fd = fd[1];
	if (sh_validate_builtin_flags(cmd))
		return (ERR_NONE);
	if (mode == EXEC_PIPE)
		sh_execute_builtin_piped(builtins[index], cmd, exec_ctx);
	else
		sh_validate_builtin_direct(builtins[index], cmd, exec_ctx);
	return (ERR_NONE);
}

int	sh_get_builtin_index(t_sh_cmd *cmd)
{
	char		*trim;
	char		**index;
	static char	*builtin_strs[8] = {"cd", "pwd", "echo", "env", "export",
		"unset", "exit", NULL};

	if (!cmd || !cmd->executable)
		return (-1);
	trim = ft_backtrim(cmd->executable, '/');
	if (!trim)
		return (-1);
	index = builtin_strs;
	while (*index && ft_strncmp(*index, trim, ft_strlen(*index) + 1))
		index++;
	free(trim);
	if (!*index)
		return (-1);
	return (index - builtin_strs);
}
