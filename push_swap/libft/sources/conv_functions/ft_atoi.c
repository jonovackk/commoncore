/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:25:04 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/30 09:43:59 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/**
 * The function converts a string that
 * represents an integer(signed or unsigned)
 * in a value of type int. It ignores leading
 * spaces, considers signs (+or-), and converts
 * numeric characters to an integer value.
 */

long	ft_atoi(const char *str)
{
	long	n;
	int		s;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	s = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			s *= -1;
		str++;
	}
	n = 0;
	while (ft_isdigit(*str))
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	return (n * s);
}
