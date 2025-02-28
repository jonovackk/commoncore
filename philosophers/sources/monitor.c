/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:08:12 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/26 13:58:58 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_philo_death(t_table *table)
{
	pthread_mutex_lock(&table->mtx_died);
	if (table->someone_died)
	{
		pthread_mutex_unlock(&table->mtx_died);
		return (1);
	}
	pthread_mutex_unlock(&table->mtx_died);
	return (0);
}

int	has_table_ended(t_table *sim)
{
	pthread_mutex_lock(&sim->mtx_end);
	if (sim->end)
	{
		pthread_mutex_unlock(&sim->mtx_end);
		return (1);
	}
	pthread_mutex_unlock(&sim->mtx_end);
	return (0);
}

static int	has_philosophers_satisfied(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mtx_eat);
	if (philo->meal_count >= philo->table->meals_needed)
	{
		pthread_mutex_unlock(&philo->table->mtx_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->mtx_eat);
	return (0);
}

static void	check_table_condition(t_table *table)
{
	int	i;

	i = 0;
	while (table->meals_needed != -1 && i < table->numb_philos
		&& has_philosophers_satisfied(&table->philo[i]))
		i++;
	if (i == table->numb_philos)
	{
		pthread_mutex_lock(&table->mtx_end);
		table->end = 1;
		pthread_mutex_unlock(&table->mtx_end);
		usleep(100);
		pthread_mutex_lock(&table->mtx_print);
		printf("number of meals eaten: %d\n", table->meals_needed);
		pthread_mutex_unlock(&table->mtx_print);
	}
}

void	monitor_death_philos(t_table *table)
{
	int	i;

	while (!has_table_ended(table))
	{
		i = -1;
		while (++i < table->numb_philos && !check_philo_death(table))
		{
			pthread_mutex_lock(&table->mtx_meal);
			if ((get_time_in_ms()
					- table->philo[i].last_meal) > table->time_to_die)
			{
				process_philo_death(table, i);
			}
			pthread_mutex_unlock(&table->mtx_meal);
			usleep(200);
		}
		if (check_philo_death(table))
			break ;
		check_table_condition(table);
	}
}
