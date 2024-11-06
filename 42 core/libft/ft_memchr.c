/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:14:18 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/29 17:23:30 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Searches for the first occurrence of byte c in the first n bytes of s.
 * Returns a pointer to the byte, or NULL if not found.
 */

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*((unsigned char *)s) == (unsigned char)c)
			return ((void *)s);
		s++;
	}
	return (NULL);
}
