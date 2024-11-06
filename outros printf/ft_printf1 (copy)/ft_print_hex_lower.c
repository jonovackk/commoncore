/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_lower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vigde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:38:01 by vigde-ol          #+#    #+#             */
/*   Updated: 2024/10/30 19:38:09 by vigde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex_lower(unsigned int num)
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
/*
Explicação:
- `hex_digits` define os caracteres para representação hexadecimal
 em minúsculas.
- `buffer` armazena os dígitos de `num` convertidos em hexadecimal, 
de trás para frente.
- O conteúdo do `buffer` é impresso na ordem correta, 
resultando na saída em hexadecimal.
- Retorna o número total de caracteres impressos.
*/
