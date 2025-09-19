/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:11:41 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/28 14:26:36 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
 * Locates the last occurrence of the character c in the string s.
 * Returns a pointer to the character in s, or NULL if c is not found.
 *
 * Parameters:
 *   s - The string to search.
 *   c - The character to locate.
 * 
 * If c is the null character, the function returns a pointer to the 
 * null terminator of the string.
 */

char	*ft_strrchr(const char *s, int c)
{
	char		*last;
	char		find;
	size_t		i;

	last = (char *)s;
	find = (char)c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (last[i] == find)
			return (last + i);
		i--;
	}
	if (last[i] == find)
		return (last);
	return (NULL);
}
