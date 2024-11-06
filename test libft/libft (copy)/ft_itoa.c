/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:53:55 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/30 09:46:16 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The 'get_size' function returns 
 * the number of digits requires
 * to store 'n'
 * including the '-' sign if negative.
 */

static unsigned int	ft_digit_count(int n)
{
	unsigned int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}
/**
 * The 'ft_itoa' function converts the 
 * integer 'n' into a string,
 * dealing with negative
 * numbers and 0, and returns the 
 * resulting string.
 */

char	*ft_itoa(int n)
{
	long			nbr;
	char			*itoa;
	unsigned int	n_digits;

	nbr = n;
	n_digits = ft_digit_count(n);
	itoa = (char *)malloc((n_digits +1) * sizeof(char));
	if (!itoa)
		return (NULL);
	itoa[n_digits--] = '\0';
	if (n < 0)
	{
		nbr = -nbr;
		itoa[0] = '-';
	}
	if (nbr == 0)
		itoa[0] = '0';
	while (nbr)
	{
		itoa[n_digits--] = '0' + (nbr % 10);
		nbr /= 10;
	}
	return (itoa);
}
