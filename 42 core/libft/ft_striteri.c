/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:58:18 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/29 14:18:25 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Applies the function f to each character of the string s,
 * passing its index and a pointer to the character.
 * 
 * Parameters:
 *   s - The string to iterate over.
 *   f - The function to apply to each character.
 * 
 * If s or f is NULL, the function does nothing.
 */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
