/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:34:03 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/27 12:24:51 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

// Determines the number of bits required to represent the largest index.
// THis is necessary for Radix Sort to know how many bits shifts to perform.
int	get_max_bits(t_stack *stack)
{
	t_stack	*current;
	int		max;
	int		bits;

	max = stack->index;
	current = stack->next;
	while (current)
	{
		if (current->index > max)
			max = current->index;
		current = current->next;
	}
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

// Counts the total number of elements in the stack.
// Used to determine the size of the stack before sorting.
int	stack_size(t_stack *stack)
{
	int	size;

	size = 0;
	while (stack)
	{
		size++;
		stack = stack->next;
	}
	return (size);
}
