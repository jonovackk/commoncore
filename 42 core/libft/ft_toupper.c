/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:13:58 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/30 10:00:30 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Converts a lowercase letter to its uppercase equivalent.
 * If the character is not a lowercase letter, it is returned unchanged.
 *
 * Parameters:
 *   c - The character to convert.
 * 
 * Returns:
 *   The uppercase equivalent of c, or c if it is not lowercase.
 */

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}
