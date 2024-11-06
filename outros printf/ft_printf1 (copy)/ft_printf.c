/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vigde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:01:14 by vigde-ol          #+#    #+#             */
/*   Updated: 2024/10/30 18:01:55 by vigde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_process_format(va_list *args, const char *format, int *count)
{
	if (*format == 'c')
		*count += ft_print_char(va_arg(*args, int));
	else if (*format == 's')
		*count += ft_print_string(va_arg(*args, char *));
	else if (*format == 'p')
		*count += ft_print_pointer(va_arg(*args, void *));
	else if (*format == 'd' || *format == 'i')
		*count += ft_print_int(va_arg(*args, int));
	else if (*format == 'u')
		*count += ft_print_unsigned(va_arg(*args, unsigned int));
	else if (*format == 'x')
		*count += ft_print_hex_lower(va_arg(*args, unsigned int));
	else if (*format == 'X')
		*count += ft_print_hex_upper(va_arg(*args, unsigned int));
	else if (*format == '%')
		*count += ft_print_percent();
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (0);
	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format)
				ft_process_format(&args, format, &count);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}
