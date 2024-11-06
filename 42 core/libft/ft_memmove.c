/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:26:52 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/29 14:37:12 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Copies n bytes from src to dest, handling overlapping memory safely.
 * Returns dest. If both dest and src are NULL, returns NULL.
 */

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (s < d && (s + n) > d)
	{
		while (n--)
			*(d + n) = *(s + n);
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}
