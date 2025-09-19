/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_revrotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:39:50 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/28 09:57:25 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"
#include "../include/custom_letters.h"

// Reverse rotates stack_a downwards (rra).
// The last element becomes the first.
// Does nothing if stack_a is empty or has only one element.
void	rev_rotate_a(t_stack **a)
{
	t_stack	*prev;
	t_stack	*last;

	if (!*a || !(*a)->next)
		return ;
	prev = NULL;
	last = *a;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *a;
	*a = last;
	ft_printf("rra\n");
}

// Revers rotates stack_b downards (rrb).
// The last element becomes the first.
// Does nothing if stack_b is empty or has only one element.
void	rev_rotate_b(t_stack **b)
{
	t_stack	*prev;
	t_stack	*last;

	if (!*b || !(*b)->next)
		return ;
	prev = NULL;
	last = *b;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *b;
	*b = last;
	ft_printf("rrb\n");
}
