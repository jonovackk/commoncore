/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:12:15 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/22 14:46:45 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_isset(char str, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == str)
			return (1);
		i++;
	}
	return (0);
}

static char	*j_pos(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	tmp;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && ft_isset(s1[i], set) == 1)
		i++;
	j = ft_strlen(s1);
	if (j > 0)
		j--;
	while (j != 0 && ft_isset(s1[j], set) == 1)
		j--;
	if (j == 0 && ft_isset(s1[j], set) == 1)
		return (j_pos());
	str = (char *)malloc(sizeof(char) * ((j - i) + 2));
	if (!str)
		return (NULL);
	tmp = 0;
	while (i <= j)
		str[tmp++] = s1[i++];
	str[tmp] = '\0';
	return (str);
}
