/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:38:13 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/28 09:57:12 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/custom_letters.h"
#include "../include/push_swap.h"

// Rotates stack_a upwards.
// The first element becomes the last.
// Does nothing if stack_a is empty or has only one element.
void	rotate_a(t_stack **a)
{
	t_stack	*first;
	t_stack	*last;

	if (!*a || !(*a)->next)
		return ;
	first = *a;
	*a = first->next;
	first->next = NULL;
	last = *a;
	while (last->next)
		last = last->next;
	last->next = first;
	ft_printf("ra\n");
}

// Rotates stack_b upwards.
// The first element becomes the last
// Does nothing if stack_b is empty or has only one element.
void	rotate_b(t_stack **b)
{
	t_stack	*first;
	t_stack	*last;

	if (!*b || !(*b)->next)
		return ;
	first = *b;
	*b = first->next;
	first->next = NULL;
	last = *b;
	while (last->next)
		last = last->next;
	last->next = first;
	ft_printf("rb\n");
}
