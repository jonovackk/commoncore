/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:28:59 by jnovack           #+#    #+#             */
/*   Updated: 2024/11/05 11:30:16 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
