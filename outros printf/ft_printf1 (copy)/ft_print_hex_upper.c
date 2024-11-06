/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_upper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vigde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:38:34 by vigde-ol          #+#    #+#             */
/*   Updated: 2024/10/30 19:38:58 by vigde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex_upper(unsigned int num)
{
	char	*hex_digits;
	char	buffer[16];
	int		i;
	int		count;

	hex_digits = "0123456789ABCDEF";
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
/*
Explicação:
- `hex_digits` define os caracteres para representação 
hexadecimal em maiúsculas.
- `buffer` armazena os dígitos convertidos de `num` em hexadecimal.
- Imprime o conteúdo de `buffer` na ordem correta.
- Retorna o número total de caracteres impressos.
*/
