/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:11:55 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/29 14:19:52 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The function resets the first 'n'
 * bytes of memory pointed to by 's'.
 * It is equivalent to a call to
 * ft_memset with value 0.
 */

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
