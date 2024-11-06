/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vigde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:35:27 by vigde-ol          #+#    #+#             */
/*   Updated: 2024/10/30 18:35:33 by vigde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Função para imprimir uma string (%s)
int	ft_print_string(char *str)
{
	int	count;

	if (!str)
		str = "(null)";
	count = 0;
	while (*str)
	{
		count += write(1, str, 1);
		str++;
	}
	return (count);
}
