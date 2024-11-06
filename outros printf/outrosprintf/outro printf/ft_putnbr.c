/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:26:14 by jnovack           #+#    #+#             */
/*   Updated: 2024/11/05 08:54:42 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	int_min(void)
{
	if (write(1, "-2147483648", 11) != 11)
		return (-1);
	return (11);
}

int	ft_putnbr(int n)
{
	int	let;
	int	temp;

	let = 0;
	if (n == -2147483648)
		return (int_min());
	if (n < 0)
	{
		if (write(1, "-", 1) != 1)
			return (-1);
		let++;
		n = -n;
	}
	if (n == 0)
	{
		if (ft_putchar('0') == -1)
			return (-1);
		return (-1);
	}
	
	if (n > 9)
	{
		temp = ft_putnbr (n /10);
		if (temp == -1)
			return (-1);
		let += temp;
	}
	if (ft_putchar ('0' + (n % 10)) == -1)
			return (-1);
	let++;
	return (let);
}
