/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_process_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:38:13 by jnovack           #+#    #+#             */
/*   Updated: 2025/06/02 11:40:29 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_error_t	sh_handle_input_line(char **i_line, t_sh_env **env)
{
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
	return (sh_quote_handler(i_line, env, 0));
}

t_error_t	sh_process_line(char **i_line, t_sh_env **env)
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
	proc_error = sh_handle_input_line(i_line, env);
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

static t_error_t	sh_handle_token_error(t_error_t status, char *error_token,
		t_sh_token **tokens, char *input_line)
{
	if (status & 0b10)
		sh_display_error(ERR_BAD_QUOTE, ": unexpected end of file");
	else
		sh_display_error(ERR_SYNTAX, error_token);
	sh_rmv_inv_parentheses(tokens);
	free(input_line);
	g_shell_exit_status = 2;
	return (ERR_FAIL_GENERAL);
}

t_error_t	sh_tokenize_input(t_sh_token **tokens, char *input_line,
		t_sh_env **environment)
{
	t_error_t	syntax_status;
	char		*error_token;

	error_token = NULL;
	if (!tokens || !input_line || !environment || !*environment)
		return (ERR_FAIL_GENERAL);
	*tokens = NULL;
	syntax_status = (!!sh_detect_quotes(input_line, NULL, QUOTE_NONE) << 1);
	*tokens = sh_tokenizer_input(input_line, QUOTE_NONE);
	syntax_status |= sh_validate_tokens(*tokens, &error_token);
	if (syntax_status & 0b11)
		return (sh_handle_token_error(syntax_status, error_token, tokens,
				input_line));
	sh_expand_tilde(tokens, sh_find_env(*environment, "HOME"));
	sh_rmv_inv_parentheses(tokens);
	if (!*tokens)
		return (free(input_line), ERR_FAIL_GENERAL);
	free(input_line);
	if (syntax_status & 0b100)
		sh_handle_heredoc_limit(*tokens, environment);
	return (ERR_NONE);
}
