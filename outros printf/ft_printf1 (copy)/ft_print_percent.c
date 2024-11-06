/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vigde-ol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:40:31 by vigde-ol          #+#    #+#             */
/*   Updated: 2024/10/30 19:40:54 by vigde-ol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_percent(void)
{
	return (write(1, "%", 1));
}

/*
Explicação:
- A função chama `write` para imprimir o caractere `%`
na saída padrão.
- Retorna `1`, indicando que um único caractere foi impresso.
*/
