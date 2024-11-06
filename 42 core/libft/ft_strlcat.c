/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:07:38 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/29 12:40:50 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Appends the string src to the end of dest up to size bytes.
 * 
 * Parameters:
 *   dest - The destination string to which src is appended.
 *   src - The source string to append.
 *   size - The total size of the destination buffer.
 * 
 * Returns the total length of the string it tried to create, which is 
 * the length of dest plus the length of src. If size is less than or
 * equal to the length of dest, it returns src_len + size.
 * 
 * If dest is NULL and size is zero, returns the length of src.
 */

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	space_left;

	src_len = ft_strlen(src);
	if (!dest && !size)
		return (src_len);
	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (src_len + size);
	space_left = size - dest_len - 1;
	dest += dest_len;
	while (space_left-- > 0 && *src)
		*dest++ = *src++;
	*dest = '\0';
	return (dest_len + src_len);
}
