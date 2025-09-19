/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:41:36 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/28 09:57:41 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/custom_letters.h"
#include "../include/push_swap.h"

// Swaps the first two elements of stack_a.
// Does nothing if stack_a has fewer than two elements.
void	swap_a(t_stack **a)
{
	t_stack	*first;
	t_stack	*second;

	if (!*a || !(*a)->next)
		return ;
	first = *a;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*a = second;
	ft_printf("sa\n");
}

// Swap the first two elements of stack_b.
// Does nothing if stack_b has fewer than two elements.
void	swap_b(t_stack **b)
{
	t_stack	*first;
	t_stack	*second;

	if (!*b || !(*b)->next)
		return ;
	first = *b;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*b = second;
	ft_printf("sb\n");
}
