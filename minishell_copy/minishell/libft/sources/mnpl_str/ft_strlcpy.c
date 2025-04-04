/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:08:31 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/30 10:00:09 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
 * Copies up to size - 1 characters from src to dest and null-terminates 
 * the result if size is greater than 0. Returns the length of the source string.
 *
 * Parameters:
 *   dest - The destination buffer.
 *   src - The source string.
 *   size - The maximum number of characters to copy.
 */

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	while (src[count])
		count++;
	if (size)
	{
		while (--size && *src)
		{
			*dest++ = *src++;
		}
		*dest = 0;
	}
	return (count);
}
