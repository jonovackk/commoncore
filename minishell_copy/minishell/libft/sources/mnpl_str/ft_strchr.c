/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:51:59 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/22 14:51:29 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
 * Locates the first occurrence of the character c in the string s.
 * Returns a pointer to the character in the string, or NULL if not found.
 * 
 * Parameters:
 *   s - The string to search.
 *   c - The character to locate (converted to unsigned char).
 */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return ((char *) s + i);
		i++;
	}
	if (s[i] == (unsigned char) c)
		return ((char *) s + i);
	return (NULL);
}
