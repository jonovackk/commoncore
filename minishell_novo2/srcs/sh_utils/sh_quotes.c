/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:58:19 by jnovack           #+#    #+#             */
/*   Updated: 2025/05/13 11:20:49 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_quote_state detect_quote_type(const char *str)
{
    if (!str)
        return QUOTE_NONE;

    while (*str == ' ')
        str++;

    size_t len = strlen(str);
    if (len < 2)
        return QUOTE_NONE;

    if (str[0] == '\'' && str[len - 1] == '\'')
        return QUOTE_SINGLE;
    if (str[0] == '\"' && str[len - 1] == '\"')
        return QUOTE_DOUBLE;

    return QUOTE_NONE;
}


