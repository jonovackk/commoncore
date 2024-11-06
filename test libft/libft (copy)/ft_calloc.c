/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:15:21 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/29 16:00:55 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * The function allocates a block of memory
 * sufficient to store 'count' elements,
 * where each elements has 'size' byters.
 * It then initializes all of that 
 * memory to zero
 */

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_bytes;

	total_bytes = nmemb * size;
	if (size && ((total_bytes / size) != nmemb))
		return (NULL);
	ptr = malloc(total_bytes);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_bytes);
	return (ptr);
}
