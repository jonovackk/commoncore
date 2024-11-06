/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:13:30 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/22 15:39:42 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Converts an uppercase letter to its lowercase equivalent.
 * If the character is not an uppercase letter, it is returned unchanged.
 *
 * Parameters:
 *   c - The character to convert.
 * 
 * Returns:
 *   The lowercase equivalent of c, or c if it is not uppercase.
 */

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}
