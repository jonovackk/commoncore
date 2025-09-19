/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:19:48 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/28 09:40:44 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

static void	sort_three_aux(t_stack **a, int first, int second, int third)
{
	if (first > second && second < third && first < third)
		swap_a(a);
	else if (first > second && second > third)
	{
		swap_a(a);
		rev_rotate_a(a);
	}
	else if (first > second && second < third && first > third)
		rotate_a(a);
	else if (first < second && second > third && first < third)
	{
		swap_a(a);
		rotate_a(a);
	}
	else if (first < second && second > third && first > third)
		rev_rotate_a(a);
}

void	sort_three(t_stack **a)
{
	int	first;
	int	second;
	int	third;

	if (!(*a) || !((*a)->next) || !((*a)->next->next))
		return ;
	first = (*a)->value;
	second = (*a)->next->value;
	third = (*a)->next->next->value;
	sort_three_aux(a, first, second, third);
}

int	get_smallest(t_stack *stack)
{
	int	min;

	min = stack->value;
	while (stack)
	{
		if (stack->value < min)
			min = stack->value;
		stack = stack->next;
	}
	return (min);
}

int	get_second_smallest(t_stack *stack)
{
	int	min;
	int	second_min;

	min = get_smallest(stack);
	second_min = INT_MAX;
	while (stack)
	{
		if (stack->value > min && stack->value < second_min)
			second_min = stack->value;
		stack = stack->next;
	}
	return (second_min);
}
