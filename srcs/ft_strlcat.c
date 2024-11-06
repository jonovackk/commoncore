/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:07:38 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/28 14:23:03 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dst, char *src, unsigned int n)
{
	char			*s;
	char			*src_start;
	unsigned int	dst_length;
	unsigned int	remaining;

	s = dst;
	src_start = src;
	remaining = n;
	while (remaining-- != 0 && *s != '\0')
		s++;
	dst_length = s - dst;
	remaining = n - dst_length;
	if (remaining == 0)
		return (dst_length + ft_strlen(src));
	while (*src != '\0')
	{
		if (remaining > 1)
		{
			*s++ = *src;
			remaining--;
		}
		src++;
	}
	*s = '\0';
	return (dst_length + (src - src_start));
}
