/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vigde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:13:53 by vigde-ol          #+#    #+#             */
/*   Updated: 2024/10/30 19:14:00 by vigde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_unsigned_fd(unsigned int n, int fd)
{
	if (n >= 10)
		ft_put_unsigned_fd(n / 10, fd);
	write(fd, &"0123456789"[n % 10], 1);
}

int	ft_print_unsigned(unsigned int n)
{
	unsigned int	num;
	int				digit_count;

	num = n;
	digit_count = 0;
	while (num > 9)
	{
		num /= 10;
		digit_count++;
	}
	digit_count++;
	ft_put_unsigned_fd(n, 1);
	return (digit_count);
}

/*
Explicação:
- `ft_put_unsigned_fd` é uma função auxiliar que imprime `unsigned int`
 sem sinal, garantindo que valores grandes sejam impressos corretamente.
- `digit_count` conta o número de dígitos do número para retornar o total
de caracteres impressos.
*/
