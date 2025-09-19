/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:36:24 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/19 10:36:49 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

// Initializes the stack from the provided arguments
// Converts each string to an integer and adds it to the stack
// Returns the created stack
// Returns NULL if there is an allocation error
// Frees the stack and returns NULL if any node fails
t_stack	*init_stack(char **argv)
{
	t_stack	*stack;
	t_stack	*node;
	int		i;

	stack = NULL;
	i = 0;
	while (argv[i])
	{
		node = new_node(ft_atoi(argv[i]));
		if (!node)
		{
			free_stack(stack);
			return (NULL);
		}
		add_node(&stack, node);
		i++;
	}
	return (stack);
}

// Checks if the stack is sorted in ascending order
// Returns 1 if sorted, 0 otherwise
int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}
