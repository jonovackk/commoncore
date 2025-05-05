/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:10:55 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/24 09:13:50 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_strlen(const char *str)
{
	int	length;

	if (!str)
		return (0);
	length = 0;
	while (str[length])
		length++;
	return (length);
}

void	ft_print_num_base(unsigned long int p, char *base, int *i)
{
	int	length;

	length = ft_strlen(base);
	if (p / length)
		ft_print_num_base(p / length, base, i);
	ft_print_char(base[p % length], i);
}
