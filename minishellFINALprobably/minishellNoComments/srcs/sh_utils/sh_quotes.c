/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:58:19 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/13 13:57:02 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_quote_state	detect_quote_type(const char *str)
{
	size_t	len;

	if (!str)
		return (QUOTE_NONE);
	while (*str == ' ')
		str++;
	len = strlen(str);
	if (len < 2)
		return (QUOTE_NONE);
	while (len > 0 && str[len - 1] == ' ')
		len--;
	if (len > 1 && str[0] == '\'' && str[len - 1] == '\'')
		return (QUOTE_SINGLE);
	if (len > 1 && str[0] == '\"' && str[len - 1] == '\"')
		return (QUOTE_DOUBLE);
	return (QUOTE_NONE);
}
