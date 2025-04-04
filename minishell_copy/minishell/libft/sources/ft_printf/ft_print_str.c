/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:14:38 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/24 09:16:01 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_print_str(char *str, int *i)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		ft_print_char(*str, i);
		str++;
	}
}
