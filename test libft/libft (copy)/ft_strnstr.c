/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:11:00 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/29 17:28:06 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Locates the first occurrence of the substring little in the string big,
 * searching only within the first len characters of big.
 * Returns a pointer to the beginning of the located substring,
 * or NULL if little is not found.
 *
 * Parameters:
 *   big - The string to search in.
 *   little - The substring to search for.
 *   len - The number of characters to search within big.
 * 
 * If little is an empty string, returns big.
 */

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (little[j] && i + j < len && big[i + j] == little[j])
				j++;
			if (!little[j])
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
