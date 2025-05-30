/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expand_tilde.c	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:24 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:06:25 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sh_expand_tilde(t_sh_token **token_list, t_sh_env *home_var)
{
	t_sh_token	*current;

	current = *token_list;
	while (current)
	{
		if (!ft_strncmp(current->content, "~", 2))
		{
			if (home_var)
			{
				free(current->content);
				current->content = sh_format_env_var(home_var, 0, 0);
			}
			current = current->next;
		}
		else
			current = current->next;
	}
}

int	sh_contains_unquoted_wildcard(char *input, t_quote_state qstat)
{
	char	*current_pos;

	current_pos = input;
	while (*current_pos)
	{
		sh_update_quote_state(*current_pos, &qstat);
		if (*current_pos == '*' && qstat == QUOTE_NONE)
			return (1);
		current_pos++;
	}
	return (0);
}

int	sh_validate_tokens(t_sh_token *tokens, char **err_token)
{
	t_sh_token	*current;
	int			here_doc_count;

	*err_token = tokens->content;
	if (!sh_validate_syntax(tokens, err_token)
		|| !sh_check_parenthesis_balance(tokens))
		return (ERR_FAIL_GENERAL);
	current = tokens;
	here_doc_count = 0;
	while (current)
	{
		here_doc_count += ((current->type & TOKEN_REDIRECT)
				&& !ft_strncmp(current->content, "<<", 3));
		current = current->next;
	}
	if (here_doc_count > 16)
		return (0b100);
	return (ERR_NONE);
}

void	sh_expd_wildcard_token(t_sh_token **token_list, t_sh_token **current)
{
	t_sh_token	*wc_tokens;
	t_sh_token	*next_token;
	t_sh_token	*prev_token;

	next_token = (*current)->next;
	wc_tokens = sh_tokenizer_input((*current)->content, QUOTE_NONE);
	sh_append_token(&wc_tokens, next_token);
	prev_token = (*current)->prev;
	sh_token_free(*current);
	if (prev_token)
	{
		prev_token->next = wc_tokens;
		prev_token = wc_tokens;
		while (prev_token != next_token)
			prev_token = prev_token->next;
		*current = prev_token;
	}
	else
	{
		*token_list = wc_tokens;
		*current = next_token;
	}
}
