/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:01:04 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/28 14:21:46 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	l1;
	size_t	l2;
	size_t	i;

	if (s1 && s2)
	{
		l1 = ft_strlen(s1);
		l2 = ft_strlen(s2);
		result = (char *) malloc(sizeof(char) * (l1 + l2 + 1));
		if (!result)
			return (NULL);
		i = 1;
		while (s1[++i])
			result[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			result[l1] = s2[i];
			l1++;
		}
		result[l1] = '\0';
		return (result);
	}
	return (NULL);
}
