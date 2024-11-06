/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:25:04 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/22 14:13:20 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The function converts a string that
 * represents an integer(signed or unsigned)
 * in a value of type int. It ignores leading
 * spaces, considers signs (+or-), and converts
 * numeric characters to an integer value.
 */

int	ft_atoi(const char *str)
{
	int	n;
	int	s;

	n = 0;
	s = 1;
	while ((*str >= 9 && *str <= 13 || *str == 32))
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			s *= -1;
		str++;
	}
	while (*str >= 48 && <= 57)
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	return (n * s);
}
