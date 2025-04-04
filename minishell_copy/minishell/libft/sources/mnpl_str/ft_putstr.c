/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:43:37 by jnovack           #+#    #+#             */
/*   Updated: 2025/01/23 16:45:42 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_putstr(char *str)
{
	int	index;

	index = 0;
	if (!str)
		index = write(1, "(null)", 6);
	else
	{
		while (str[index] != '\0')
		{
			write (1, &str[index], 1);
			index++;
		}
	}
	return (index);
}
