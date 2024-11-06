/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:55:28 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/22 15:38:20 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	size_t	size;

	size = ft_strlen(src) +1;
	dst = (char *) malloc(size);
	if (!dst)
		return (NULL);
	ft_memcpy(dst, src, size);
	return (dst);
}
