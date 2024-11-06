/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vigde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:35:16 by vigde-ol          #+#    #+#             */
/*   Updated: 2024/10/30 19:35:30 by vigde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_hex(unsigned long num)
{
	char	*hex_digits;
	char	buffer[16];
	int		i;
	int		count;

	hex_digits = "0123456789abcdef";
	i = 0;
	if (num == 0)
		buffer[i++] = '0';
	while (num > 0)
	{
		buffer[i++] = hex_digits[num % 16];
		num /= 16;
	}
	count = i;
	while (--i >= 0)
		write(1, &buffer[i], 1);
	return (count);
}

int	ft_print_pointer(void *ptr)
{
	int	count;

	if (!ptr)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	count += ft_print_hex((unsigned long)ptr);
	return (count);
}
/*
Explicação:
- `ft_print_hex` converte um número para hexadecimal e imprime os 
caracteres na ordem correta.
- `ft_print_pointer` imprime o prefixo "0x" para indicar um ponteiro.
- Se `ptr` for `NULL`, imprime "0". Caso contrário, chama `ft_print_hex` 
para imprimir o valor hexadecimal.
- A função retorna o número total de caracteres impressos, incluindo o "0x".
*/
