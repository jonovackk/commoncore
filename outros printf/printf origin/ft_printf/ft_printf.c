/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:59:24 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/31 12:11:33 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"


static void	ft_printf_checker(va_list args, const char *str, int *count)
{
	if (*str == 'c')
		ft_putchar_count(va_arg(args, int), count);
	else if (*str == 's')
		ft_putstr_count(va_arg(args, char *), count);
	else if (*str == 'p')
		ft_putptr_count(va_arg(args, void *), count);
	else if (*str == 'd')
		ft_putnbr_count(va_arg(args, int), count);
	else if (*str == 'u')
		ft_putnbr_unsigned_count(va_arg(args, unsigned int), count);
	else if (*str == 'x')
		ft_put_hex_count(va_arg(args, unsigned int), "0123456789abcdef", count);
	else if (*str == 'X')
		ft_put_hex_count(va_arg(*args, int), "0123456789ABCDEF", count);
	else if (*str == '%')
		ft_putchar_count('%', count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			str++;
			ft_handle_arg(args, str, &count);
		}
		else
		{
			ft_putchar_count(*str, &count);
			str++;
		}
	}
	return (count);
}
