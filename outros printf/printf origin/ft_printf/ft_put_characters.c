/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_characters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:12:27 by jnovack           #+#    #+#             */
/*   Updated: 2024/10/31 13:35:35 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	ft_putchar_count(int c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_putstr_count(char *str, int *count)
{
	if (!str)
	{
		ft_putstr_count("(null)", count);
		return ;
	}
	while (*str)
		ft_putchar_count(*str++, count);
}

