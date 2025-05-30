/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_psng_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:06:28 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/12 15:06:29 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_update_quote_state(char c, t_quote_state *qstatus)
{
	t_quote_state	previous;

	previous = *qstatus;
	if (*qstatus == QUOTE_NONE)
	{
		if (c == '\'')
			*qstatus = QUOTE_SINGLE;
		if (c == '"')
			*qstatus = QUOTE_DOUBLE;
	}
	else if ((c == '\'' && *qstatus == QUOTE_SINGLE) || (c == '"'
			&& *qstatus == QUOTE_DOUBLE))
		*qstatus = QUOTE_NONE;
	return (*qstatus != previous);
}

int	sh_ignoring_quotes(char *str)
{
	t_quote_state	qstatus;
	int				length;

	qstatus = QUOTE_NONE;
	length = 0;
	while (*str)
	{
		if (!sh_update_quote_state(*(str++), &qstatus))
			length++;
	}
	return (length);
}

void	sh_rmv_inv_parentheses(t_sh_token **tokens)
{
	t_sh_token	*current;

	current = *tokens;
	while (current)
	{
		if (!sh_check_ops_in_brackets(current))
		{
			sh_delete_token(&current);
			if (!current)
			{
				*tokens = NULL;
				continue ;
			}
			if (!current->prev)
				*tokens = current;
			continue ;
		}
		current = current->next;
	}
}
