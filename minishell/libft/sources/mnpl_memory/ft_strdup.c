/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:55:28 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/29 16:16:35 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
 * Duplicates the string s by allocating new memory and copying its content.
 * 
 * Returns a pointer to the duplicated string, or NULL if allocation fails.
 * The new string is null-terminated.
 */

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	s_length;

	s_length = ft_strlen(s);
	dup = ft_calloc(s_length + 1, sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, s_length +1);
	return (dup);
}
