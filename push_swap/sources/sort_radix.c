/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_radix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:30:56 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/27 11:38:14 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

// Implements the Radix Sort algorithm for sorting the stack.
// Works with normalized values (0 to n-1) for efficiency.
// Uses bitwise operations to distribute numbers based on their bits.
// Shifts elements between stack_a and stack_b according to the bits.
// Continues until all bits are processed, ensuring the stack is sorted.
void	radix_sort(t_stack **stack_a, t_stack **stack_b)
{
	int		max_bits;
	int		size;
	int		i;
	int		j;
	t_stack	*current;

	size = stack_size(*stack_a);
	max_bits = get_max_bits(*stack_a);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			current = *stack_a;
			if (((current->index >> i) & 1) == 0)
				push_b(stack_a, stack_b);
			else
				rotate_a(stack_a);
			j++;
		}
		while (*stack_b != NULL)
			push_a(stack_a, stack_b);
		i++;
	}
}
