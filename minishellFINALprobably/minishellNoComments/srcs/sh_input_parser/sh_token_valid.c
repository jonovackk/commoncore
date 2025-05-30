/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_token_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:36 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:06:37 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_validate_subtoken(t_sh_token *token)
{
	t_token_kind	binop_mask;
	t_token_kind	str_mask;

	binop_mask = TOKEN_LOGICAL | TOKEN_PIPE;
	str_mask = TOKEN_TEXT | TOKEN_REDIRECT;
	if ((token->type & TOKEN_LOGICAL) && (token->next->type & binop_mask))
		return (0);
	else if (token->type == TOKEN_REDIRECT && !(token->next->type & TOKEN_TEXT))
		return (0);
	else if (token->type == TOKEN_PIPE && (token->next->type & binop_mask))
		return (0);
	else if (!ft_strncmp(token->content, "(", 2)
		&& ((token->next->type & binop_mask)
			|| !ft_strncmp(token->next->content, ")", 2)))
		return (0);
	else if (token->type == TOKEN_TEXT
		&& (token->next->type & TOKEN_PARENTHESIS)
		&& !ft_strncmp(token->next->content, "(", 2))
		return (0);
	else if (!ft_strncmp(token->content, ")", 2)
		&& (token->next->type & str_mask || !ft_strncmp(token->next->content,
				"(", 2)))
		return (0);
	return (1);
}

int	sh_validate_syntax(t_sh_token *token, char **err_token)
{
	if (token->type & (TOKEN_LOGICAL | TOKEN_PIPE))
		return (0);
	while (token->next)
	{
		*err_token = token->next->content;
		if (!sh_validate_subtoken(token))
			return (0);
		token = token->next;
	}
	return (token->type & (TOKEN_PARENTHESIS | TOKEN_TEXT));
}

int	sh_check_parenthesis_balance(t_sh_token *tokens)
{
	int	balance;

	balance = 0;
	while (tokens != NULL)
	{
		if ((tokens->type & TOKEN_PARENTHESIS) && !ft_strncmp(tokens->content,
				"(", 2))
			balance++;
		else if ((tokens->type & TOKEN_PARENTHESIS)
			&& !ft_strncmp(tokens->content, ")", 2))
			balance--;
		if (balance < 0)
			return (0);
		tokens = tokens->next;
	}
	return (balance == 0);
}

static int	check_ops_inside(t_sh_token *token)
{
	int	valid;
	int	bracket_level;

	bracket_level = 0;
	valid = 0;
	while (token && (!(token->type & TOKEN_PARENTHESIS
				&& !ft_strncmp(token->content, ")", 2)) || bracket_level))
	{
		if (token->type & TOKEN_PARENTHESIS
			&& !ft_strncmp(token->content, "(", 2))
			bracket_level++;
		if (token->type & TOKEN_PARENTHESIS
			&& !ft_strncmp(token->content, ")", 2))
			bracket_level--;
		if (!bracket_level && (token->type & TOKEN_LOGICAL))
			valid = 1;
		token = token->next;
	}
	if (!token)
		return (1);
	if (!(token && valid))
		sh_delete_token(&token);
	return (token && valid);
}

int	sh_check_ops_in_brackets(t_sh_token *token)
{
	if (!token || !(token->type & TOKEN_PARENTHESIS
			&& !ft_strncmp(token->content, "(", 2)))
		return (1);
	return (check_ops_inside(token->next));
}
