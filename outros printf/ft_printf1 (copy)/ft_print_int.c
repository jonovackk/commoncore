/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vigde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:43:48 by vigde-ol          #+#    #+#             */
/*   Updated: 2024/10/30 18:43:58 by vigde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_int(int n)
{
	int				digit_count;
	unsigned int	num;

	digit_count = 0;
	if (n < 0)
	{
		digit_count++;
		num = -n;
	}
	else
		num = n;
	while (num > 9)
	{
		num /= 10;
		digit_count++;
	}
	digit_count++;
	ft_putnbr_fd(n, 1);
	return (digit_count);
}
/*
Explicação:
- `digit_count` é incrementado para contar o sinal se `n` for negativo.
- `num` é usado para contar os dígitos sem modificar `n`.
- `ft_putnbr_fd(n, 1)` imprime `n`, pois `ft_putnbr_fd` 
já lida com o sinal negativo.
*/
