/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_normalize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:16:23 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/27 11:45:50 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

// Fills an array with the values from the stack.
// Returns a pointer to the array.
static int	*fill_array(t_stack *stack, int size)
{
	int	*arr;
	int	i;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (stack)
	{
		arr[i++] = stack->value;
		stack = stack->next;
	}
	return (arr);
}

// Sorts an array of integers in ascending order.
static void	sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

// Finds the index of a value in a sorted array.
// Returns the index if found, or -1 if not found.
static int	get_index(int *arr, int size, int value)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (arr[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

// Normalize the values in the stack by replacing each value
// With it index the sorted version of the stack values.
void	normalize_values(t_stack *stack)
{
	int		*arr;
	int		size;
	t_stack	*current;

	size = stack_size(stack);
	arr = fill_array(stack, size);
	if (!arr)
		return ;
	sort_array(arr, size);
	current = stack;
	while (current)
	{
		current->index = get_index(arr, size, current->value);
		current = current->next;
	}
	free(arr);
	print_stack(stack);
}
