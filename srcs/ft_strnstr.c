/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:11:00 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/28 14:24:41 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *to_find, size_t n)
{
	unsigned int	pos;
	unsigned int	i;

	if (!*to_find)
		return ((char *)s);
	pos = 0;
	while (s[pos] && (size_t)pos < n)
	{
		if (s[pos] == to_find[0])
		{
			i = 1;
			while (to_find[i] && s[pos + i] == to_find[i]
				&& (size_t)(pos + i) < n)
				i++;
			if (to_find[i] == '\0')
				return ((char *)&s[pos]);
		}
		pos++;
	}
	return (NULL);
}
