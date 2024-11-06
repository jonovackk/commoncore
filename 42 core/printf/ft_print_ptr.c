/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:26:54 by jnovack           #+#    #+#             */
/*   Updated: 2024/11/05 11:28:44 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_ptr(void *ptr, int *i)
{
	unsigned long	p;

	p = (unsigned long) ptr;
	if (p)
	{
		ft_print_str("0x", i);
		ft_print_num_base(p, "0123456789abcdef", i);
	}
	else
		ft_print_str("(nil)", i);
}
