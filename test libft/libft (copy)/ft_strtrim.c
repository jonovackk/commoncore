/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:12:15 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/29 16:45:28 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Removes leading and trailing characters from the string s1
 * that are contained in the set string.
 * Returns a new string with the trimmed result, or NULL if 
 * allocation fails or if s1 or set is NULL.
 *
 * Parameters:
 *   s1 - The string to be trimmed.
 *   set - The set of characters to remove.
 */

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	trimmed_len;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	trimmed_len = ft_strlen(s1);
	while (*s1 && ft_strchr(set, *s1))
	{
		s1++;
		trimmed_len--;
	}
	while (trimmed_len && ft_strchr(set, s1[trimmed_len - 1]))
		trimmed_len--;
	result = (char *)malloc(trimmed_len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, trimmed_len + 1);
	return (result);
}
