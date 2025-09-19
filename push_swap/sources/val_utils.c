/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:42:59 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/19 10:43:32 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

// Validates the input arguments.
// Checks if all arguments are numbers and within INT limits.
// Returns 1 if valid, 0 otherwise.
int	validate_input(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!is_number(argv[i]) || ft_atoi(argv[i]) > INT_MAX
			|| ft_atoi(argv[i]) < INT_MIN)
			return (0);
		i++;
	}
	return (1);
}

// Checks if a string is a valid number.
// Allows optional + or - sign followed by digits.
// Returns 1 if valid, 0 otherwise.
int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
