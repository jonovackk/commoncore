/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:26:07 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/21 17:26:07 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_all_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->mtx_meal, NULL))
		return (printf("meal Error\n"), 0);
	if (pthread_mutex_init(&table->mtx_end, NULL))
		return (printf("end Error\n"), 0);
	if (pthread_mutex_init(&table->mtx_print, NULL))
		return (printf("print Error\n"), 0);
	if (pthread_mutex_init(&table->mtx_died, NULL))
		return (printf("died Error\n"), 0);
	if (pthread_mutex_init(&table->mtx_eat, NULL))
		return (printf("eat Error\n"), 0);
	return (1);
}

int	init_mutexes(t_table *table)
{
	int	i;

	i = -1;
	table->fork = malloc(sizeof(t_fork) * table->numb_philos);
	if (!table->fork)
		return (printf("error\n"), 0);
	while (++i < table->numb_philos)
	{
		if (pthread_mutex_init(&table->fork[i].mutex, NULL))
			return (printf("fork error!\n"), 0);
		table->fork[i].philo_pick = 0;
	}
	return (init_all_mutexes(table));
}

void	run_table(t_table *table)
{
	int		i;
	void	*routine;

	i = -1;
	if (table->numb_philos == 1)
		routine = philo_routine;
	else
		routine = philosopher_thread;
	table->start_time = get_time_in_ms();
	while (++i < table->numb_philos)
	{
		table->philo[i].last_meal = table->start_time;
		if (pthread_create(&table->philo[i].thread, NULL, routine,
				&table->philo[i]) != 0)
		{
			printf("thread creating error %d\n", table->philo[i].id);
		}
	}
	if (routine == philosopher_thread)
		monitor_death_philos(table);
}

int	setup_philos(t_table *table)
{
	int	i;

	i = -1;
	table->philo = malloc(sizeof(t_philo) * table->numb_philos);
	if (table->philo == NULL)
	{
		printf("memory allocating error!\n");
		return (0);
	}
	while (++i < table->numb_philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].last_meal = 0;
		table->philo[i].right_fork = i;
		table->philo[i].left_fork = (i + 1) % table->numb_philos;
		table->philo[i].meal_count = 0;
		table->philo[i].table = table;
	}
	return (1);
}
