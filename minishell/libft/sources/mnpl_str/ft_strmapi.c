/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:09:41 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/29 14:13:34 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
 * Applies function f to each character of string s, returning a new string
 * with the results. The function f receives the index and character.
 *
 * Parameters:
 *   s - Input string.
 *   f - Function to apply to each character.
 * 
 * Returns a new string or NULL if allocation fails or if s or f is NULL.
 */

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*mapi;
	unsigned int	i;

	if (!f || !s)
		return (NULL);
	mapi = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!mapi)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	mapi[i] = '\0';
	return (mapi);
}
