/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_input_tokenizer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:24 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:06:25 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_is_shell_operator(char *input, t_quote_state qstat)
{
	char		**current;
	static char	*operators[11] = {" ", "(", ")", "||", "&&", "|", ">>", ">",
		"<<", "<", NULL};

	current = operators;
	if (!input || !*input)
		return (1);
	if (isspace(*input) && qstat == QUOTE_NONE)
		return (1);
	while (*current && (ft_strncmp(input, *current, ft_strlen(*current))
			|| qstat != QUOTE_NONE))
		current++;
	if (*current)
		return (ft_strlen(*current));
	return (0);
}

t_token_kind	sh_classify_token(char **input, t_quote_state qstat)
{
	if (qstat != QUOTE_NONE)
		return (TOKEN_TEXT);
	if (!ft_strncmp(*input, "(", 1) || !ft_strncmp(*input, ")", 1))
		return (TOKEN_PARENTHESIS);
	if (!ft_strncmp(*input, "||", 2) || !ft_strncmp(*input, "&&", 2))
		return (TOKEN_LOGICAL);
	if (!ft_strncmp(*input, "|", 1))
		return (TOKEN_PIPE);
	if (!ft_strncmp(*input, ">", 1) || !ft_strncmp(*input, "<", 1))
		return (TOKEN_REDIRECT);
	return (TOKEN_TEXT);
}

static char	*sh_tokenizer_extract_token(char *input, t_quote_state *qstat)
{
	char	*current_pos;
	int		token_length;

	current_pos = input;
	token_length = sh_is_shell_operator(current_pos, *qstat);
	while (*current_pos && (!token_length || (isspace(*current_pos)
				&& *qstat != QUOTE_NONE)))
	{
		sh_update_quote_state(*current_pos, qstat);
		current_pos++;
		token_length = sh_is_shell_operator(current_pos, *qstat);
	}
	if (current_pos == input)
		return (ft_strndup(input, token_length));
	return (ft_strndup(input, current_pos - input));
}

static t_sh_token	*sh_tokenizer_create_token(char *token_content,
		t_quote_state qstat)
{
	t_sh_token	*result;
	char		*token_copy;

	result = NULL;
	if (ft_strncmp(token_content, " ", 2) != 0)
	{
		token_copy = ft_strdup(token_content);
		result = sh_create_token(&token_copy,
				sh_classify_token(&token_content, qstat));
		free(token_copy);
	}
	return (result);
}

t_sh_token	*sh_tokenizer_input(char *input, t_quote_state qstat)
{
	t_sh_token	*result;
	char		*token_content;

	result = NULL;
	if (!input || !*input)
		return (NULL);
	token_content = sh_tokenizer_extract_token(input, &qstat);
	result = sh_tokenizer_create_token(token_content, qstat);
	sh_append_token(&result, sh_tokenizer_input
		(input + ft_strlen(token_content), qstat));
	free(token_content);
	return (result);
}
