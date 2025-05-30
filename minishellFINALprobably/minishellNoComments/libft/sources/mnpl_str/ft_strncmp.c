/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:10:21 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/22 16:21:20 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
 * Compares up to n characters of the strings s1 and s2.
 * Returns 0 if they are equal, a positive value if s1 > s2,
 * or a negative value if s1 < s2.
 *
 * Parameters:
 *   s1 - First string to compare.
 *   s2 - Second string to compare.
 *   n - Maximum number of characters to compare.
 * 
 * If n is 0, the function returns 0.
 */

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (s1 != s2);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
