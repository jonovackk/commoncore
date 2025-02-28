/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:21:50 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/26 13:58:09 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	validate_argument(int value, int index)
{
	if (index == 1 && value > 200)
		return (printf("max %d\n", 200), 0);
	if (index == 5)
	{
		if (value == -1)
			return (1);
		if (value < 1 && value != -1)
			return (printf("over 1 meal\n"), 0);
	}
	return (1);
}

static int	parse_arguments(int argc, t_table *table, char **argv)
{
	table->numb_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->end = 0;
	table->someone_died = 0;
	table->meals_needed = -1;
	if (argc == 6)
		table->meals_needed = ft_atoi(argv[5]);
	return (1);
}

static int	validate_inputs(int argc, char **argv)
{
	int	i;
	int	value;

	i = 1;
	while (i < argc)
	{
		value = ft_atoi(argv[i]);
		if (validate_argument(value, i))
		{
			if (value <= 0 && !(i == 5 && value == -1))
			{
				printf("incorrect value: %s !\n", argv[i]);
				return (0);
			}
		}
		else
			return (0);
		i++;
	}
	return (1);
}

static int	validate_number_of_arguments(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep [meals_required]\n");
		return (0);
	}
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
				return (printf("Invalid input: %s\n", argv[i]), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!validate_number_of_arguments(argc, argv))
		return (1);
	if (!validate_inputs(argc, argv))
		return (1);
	if (!parse_arguments(argc, &table, argv))
		return (1);
	if (!setup_philos(&table))
	{
		destroy_mutexes(&table);
		return (1);
	}
	if (!init_mutexes(&table))
	{
		destroy_mutexes(&table);
		return (1);
	}
	run_table(&table);
	end_table(&table);
	return (0);
}
