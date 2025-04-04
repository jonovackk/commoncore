/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:24:22 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/24 08:30:23 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_print_num(int num, int *i)
{
	if (num == -2147483648)
	{
		ft_print_num((num / 10), i);
		ft_print_char('8', i);
	}
	else if (num < 0)
	{
		ft_print_char('-', i);
		ft_print_num(-num, i);
	}
	else
	{
		if (num > 9)
			ft_print_num((num / 10), i);
		ft_print_char((char)('0' + num % 10), i);
	}
}
