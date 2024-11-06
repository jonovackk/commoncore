/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:53:55 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/22 15:35:04 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The 'get_size' function returns 
 * the number of digits requires
 * to store 'n'
 * including the '-' sign if negative.
 */

static size_t	get_size(int n)
{
	size_t	size;

	if (n > 0)
		size = 1;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
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
	char	*result;
	long	num;
	size_t	size;

	num = (long) n;
	size = get_size(n);
	if (n < 0)
		num *= -1;
	result = (char *) malloc(size + 1);
	if (!result)
		return (NULL);
	*(result + size--) = '\0';
	while (num > 0)
	{
		*(result + size--) = (num % 10) + '0';
		num /= 10;
	}
	if (size == 0 && result[1] == '\0')
		*(result + size) = '0';
	else if (size == 0 && result[1])
		*(result + size) = '-';
	return (result);
}
