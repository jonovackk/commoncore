/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_processor_pt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:17 by jnovack           #+#    #+#             */
/*   Updated: 2025/06/02 11:47:05 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sh_wait_all_processes(t_sh_exec *executor)
{
	t_sh_pid	*waiting_process;
	int			process_exit_code;

	while (executor->running_procs)
	{
		waiting_process = sh_pid_pop(&(executor->running_procs));
		if (!waiting_process)
			continue ;
		waitpid(waiting_process->pid, &process_exit_code, 0);
		g_shell_exit_status = WEXITSTATUS(process_exit_code);
		sh_process_command_exit(process_exit_code);
		free(waiting_process);
	}
}

t_error_t	sh_execute_command_tree(t_sh_token **tokens,
		t_sh_node **execution_tree, t_sh_env **environment)
{
	t_sh_exec	*executor;
	static int	base_fd[2] = {0, 1};

	if (!tokens || !*tokens)
		return (ERR_FAIL_GENERAL);
	*execution_tree = sh_build_tree(*tokens, environment);
	sh_free_token_list(*tokens);
	sh_command_tree_state(0, *execution_tree);
	if (!*execution_tree)
		return (ERR_FAIL_GENERAL);
	if (sh_process_heredoc(*execution_tree))
		return (ERR_HEREDOC_ABORTED);
	executor = sh_exec_init();
	if (!executor)
	{
		sh_tree_fd_cleanup(*execution_tree);
		sh_destroy_tree(*execution_tree);
		return (ERR_FAIL_GENERAL);
	}
	sh_configure_signal_state(HANDLER_IGN);
	sh_execute_command_multiplex(*execution_tree, base_fd, executor, EXEC_WAIT);
	sh_wait_all_processes(executor);
	sh_configure_signal_state(HANDLER_INTERRUPT);
	free(executor);
	return (ERR_NONE);
}

t_error_t	sh_process_heredoc(t_sh_node *execution_tree)
{
	int	heredoc_completed;

	if (!execution_tree)
		return (ERR_FAIL_GENERAL);
	heredoc_completed = 0;
	if (sh_traverse_heredocs(execution_tree,
			&heredoc_completed) == ERR_HEREDOC_ABORTED)
	{
		sh_tree_fd_cleanup(execution_tree);
		sh_destroy_tree(execution_tree);
		return (ERR_FAIL_GENERAL);
	}
	return (ERR_NONE);
}

void	sh_handle_prompt(t_sh_env **environment)
{
	char		*input_line;
	t_sh_token	*tokens;
	t_sh_node	*execution_tree;

	if (!environment || !*environment)
		return ;
	input_line = NULL;
	tokens = NULL;
	execution_tree = NULL;
	if (sh_process_line(&input_line, environment))
		return ;
	if (sh_tokenize_input(&tokens, input_line, environment) || !tokens)
		return ;
	if (sh_execute_command_tree(&tokens, &execution_tree, environment))
		return ;
	sh_tree_fd_cleanup(execution_tree);
	sh_destroy_tree(execution_tree);
}
