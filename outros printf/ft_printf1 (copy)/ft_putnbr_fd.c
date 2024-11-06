/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vigde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:25:53 by vigde-ol          #+#    #+#             */
/*   Updated: 2024/10/24 17:26:25 by vigde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include "ft_printf.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (n < 0)
	{
		write(fd, "-", 1);
		num = -n;
	}
	else
		num = n;
	if (num >= 10)
		ft_putnbr_fd(num / 10, fd);
	write(fd, &"0123456789"[num % 10], 1);
}
/*
Explicação:
- Se `n` for negativo, imprime o sinal '-' e converte `n` 
para positivo usando `unsigned int`.
- Em seguida, usa recursão para imprimir os dígitos, dividindo 
`num` por 10 até restar apenas um dígito.
- A chamada `write(fd, &"0123456789"[num % 10], 1);` imprime cada 
dígito final na ordem correta.
*/
