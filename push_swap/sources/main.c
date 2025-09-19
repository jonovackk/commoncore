/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:14:55 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/27 10:49:55 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/custom_letters.h"
#include "../include/push_swap.h"

// Entry point of the push_swap program.
// Handles arguments, validates input, initializes the stack,
// normalizes values, sorts the stack using radix sort, and frees memory.
// First condition: Handle empty input and single empty string.
// 2 condition: Split arguments if passed as a single string.
// 3 condition: Validate input (numbers, no duplicates, within int limits).
// 4 condition: Initialize stack with valid input values.
// 5 condition: Perform sorting only if stack is not already sorted.
// Last condition: Free allocated memory.

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2 || (argc == 2 && argv[1][0] == '\0'))
		return (0);
	if (argc == 2)
		argv = ft_split(argv[1], ' ');
	else
		argv++;
	if (!validate_input(argv) || check_duplicates(argv))
	{
		ft_printf("%sError\n%s", COLOR_RED, COLOR_DEFAULT);
		if (argc == 2)
			ft_free_all(argv);
		return (0);
	}
	stack_a = init_stack(argv);
	normalize_values(stack_a);
	print_stack(stack_a);
	stack_b = NULL;
	sort_stack(&stack_a, &stack_b);
	free_stack(stack_a);
	if (argc == 2)
		ft_free_all(argv);
	return (0);
}
