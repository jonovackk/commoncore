/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:24:26 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/30 09:48:55 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Copies n bytes from src to dest. 
 * Returns dest. If both dest and src are NULL, returns NULL.
 */

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	const char		*s;

	if (!dest && ! src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
