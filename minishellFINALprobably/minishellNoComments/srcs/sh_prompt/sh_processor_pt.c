/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_processor_pt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:08:17 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/30 15:53:00 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

error_t	sh_process_line(char **i_line, t_sh_env **env)
{
	char	*p_str;
	int		proc_error;

	if (!i_line || !env || !*env)
		return (ERR_FAIL_GENERAL);
	*i_line = NULL;
	p_str = sh_get_prompt(*env);
	if (!p_str)
		return (ERR_FAIL_GENERAL);
	*i_line = readline("minishell > ");
	free(p_str);
	p_str = NULL;
	if (!*i_line)
	{
		write(1, "exit\n", 5);
		sh_destroy_env_list(*env);
		exit(g_shell_exit_status);
	}
	if (!is_non_empty(*i_line))
	{
		free(*i_line);
		*i_line = NULL;
		return (ERR_FAIL_GENERAL);
	}
	add_history(*i_line);
	sh_configure_signal_state(HANDLER_IGN);
	proc_error = sh_quote_handler(i_line, env, 0);
	sh_configure_signal_state(HANDLER_INTERRUPT);
	if (proc_error == ERR_ERRORS)
	{
		sh_destroy_env_list(*env);
		sh_execute_exit(NULL);
	}
	else if (proc_error == ERR_FAIL_GENERAL || !*i_line)
	{
		g_shell_exit_status = 130;
		return (ERR_DQUOTE_ABORTED);
	}
	return (ERR_NONE);
}

error_t	sh_tokenize_input(t_sh_token **tokens, char *input_line,
		t_sh_env **environment)
{
	error_t	syntax_status;
	char	*error_token;

	error_token = NULL;
	if (!tokens || !input_line || !environment || !*environment)
		return (ERR_FAIL_GENERAL);
	*tokens = NULL;
	syntax_status = (!!sh_detect_quotes(input_line, NULL, QUOTE_NONE) << 1);
	*tokens = sh_tokenizer_input(input_line, QUOTE_NONE);
	syntax_status |= sh_validate_tokens(*tokens, &error_token);
	if (syntax_status & 0b11)
	{
		if (syntax_status & 0b10)
			sh_display_error(ERR_BAD_QUOTE, ": unexpected end of file");
		else
			sh_display_error(ERR_SYNTAX, error_token);
		sh_rmv_inv_parentheses(tokens);
		free(input_line);
		input_line = NULL;
		g_shell_exit_status = 2;
		return (ERR_FAIL_GENERAL);
	}
	sh_expand_tilde(tokens, sh_find_env(*environment, "HOME"));
	sh_rmv_inv_parentheses(tokens);
	if (!*tokens)
	{
		free(input_line);
		input_line = NULL;
		return (ERR_FAIL_GENERAL);
	}
	free(input_line);
	input_line = NULL;
	if (syntax_status & 0b100)
		sh_handle_heredoc_limit(*tokens, environment);
	return (ERR_NONE);
}

error_t	sh_execute_command_tree(t_sh_token **tokens, t_sh_node **execution_tree,
		t_sh_env **environment)
{
	t_sh_exec	*executor;
	t_sh_pid	*waiting_process;
	int			process_exit_code;
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
	while (executor->running_procs)
	{
		waiting_process = sh_pid_pop(&(executor->running_procs));
		if (waiting_process)
		{
			waitpid(waiting_process->pid, &process_exit_code, 0);
			g_shell_exit_status = WEXITSTATUS(process_exit_code);
			sh_process_command_exit(process_exit_code);
			free(waiting_process);
		}
	}
	sh_configure_signal_state(HANDLER_INTERRUPT);
	free(executor);
	return (ERR_NONE);
}

error_t	sh_process_heredoc(t_sh_node *execution_tree)
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
