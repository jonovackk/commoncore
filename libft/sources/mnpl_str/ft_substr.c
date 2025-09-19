/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:12:57 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/29 16:27:43 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/*
 * Allocates and returns a substring from the string s.
 * The substring starts at index 'start' and has a maximum length of 'len'.
 * Returns NULL if allocation fails or if s is NULL.
 *
 * Parameters:
 *   s - The source string.
 *   start - The starting index of the substring.
 *   len - The maximum length of the substring.
 */

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	size_t			s_len;
	unsigned int	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < (unsigned int)len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
