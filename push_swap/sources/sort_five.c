/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:07:05 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/27 14:22:30 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	push_smallest_to_b(t_stack **a, t_stack **b)
{
	int	smallest;

	smallest = get_smallest(*a);
	while ((*a)->value != smallest)
	{
		if (get_position(*a, smallest) <= stack_size(*a) / 2)
			rotate_a(a);
		else
			rev_rotate_a(a);
	}
	push_b(a, b);
}

void	sort_five(t_stack **a, t_stack **b)
{
	push_smallest_to_b(a, b);
	push_smallest_to_b(a, b);
	sort_three(a);
	if ((*b)->value < (*b)->next->value)
		swap_b(b);
	push_a(a, b);
	push_a(a, b);
}

int	get_position(t_stack *stack, int value)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->value == value)
			return (pos);
		stack = stack->next;
		pos++;
	}
	return (-1);
}
