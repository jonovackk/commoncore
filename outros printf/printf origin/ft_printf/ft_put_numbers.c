/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_numbers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:27:37 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/31 11:58:56 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

/**
 * Imprime um num. na base hex fornecida.
 *
 * @param ptr numero a ser impresso em hex.
 * @param hex_digits alfabeto hex a ser utilizado
 * @param count ponteiro para a contagem de caracteres impressos.
*/

void	ft_put_hex_count(unsigned long ptr, const char *hex_digits, int *count)
{
	if (ptr >= 16)
	{
		ft_put_hex_count(ptr / 16, hex_digits, count);
	}
	ft_putchar_count(hex_digits[ptr % 16], count);


/**
 *
 *
 *
 *
 *
*/

void	ft_putptr_count(void *ptr, int *count)
{
	if (!ptr)
	{
		ft_putstr_count("(nil)", count);
		return ;
	}
	ft_putstr_count("0x", count);
	ft_put_hex_count((unsigned long)ptr, "0123456789abcdef", count);
}

/**
 *
 *
 *
 *
 *
 *
*/

void	ft_putnbr_unsigned_count(unsigned int nbr, int *count)
{
	if (nbr >= 10)
	{
		ft_putnbr_count(nbr / 10, count);
		ft_putchar_count('0' + nbr % 10, count);
	}
	else
		ft_putchar_count('0' + nbr % 10, count);
}

/**unsigned int
 *
 *
 *
 *
 *
*/
void	ft_putnbr_count(int nbr, int *count)
{
	if (nbr < 0)
	{
		ft_putchar_count('-', count);
		nbr = -nbr;
	}
	ft_putnbr_unsigned_count(nbr, count);
}
