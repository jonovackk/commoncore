/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:40:20 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/22 16:31:13 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
 * Outputs the integer n to the given file descriptor fd.
 * Handles negative numbers by printing a minus sign.
 * 
 * Parameters:
 *   n  - The integer to output.
 *   fd - The file descriptor to which the integer is written.
 */

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = (unsigned int)(n * -1);
	}
	else
		num = (unsigned int)n;
	if (num >= 10)
		ft_putnbr_fd(num / 10, fd);
	ft_putchar_fd(num % 10 + 48, fd);
}
