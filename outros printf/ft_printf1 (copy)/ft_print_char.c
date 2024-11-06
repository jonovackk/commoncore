/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vigde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:23:49 by vigde-ol          #+#    #+#             */
/*   Updated: 2024/10/30 18:23:54 by vigde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Função para imprimir um único caractere (%c)
int	ft_print_char(char c)
{
	int	ret;

	ret = write(1, &c, 1);
	return (ret);
}
