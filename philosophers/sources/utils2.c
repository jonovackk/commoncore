/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:09:30 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/28 11:55:33 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	process_philo_death(t_table *table, int i)
{
	pthread_mutex_lock(&table->mtx_died);
	table->someone_died = 1;
	pthread_mutex_unlock(&table->mtx_died);
	pthread_mutex_lock(&table->mtx_print);
	printf("%ld %d %s\n", get_time_in_ms() - table->start_time,
		table->philo[i].id, "died.");
	pthread_mutex_unlock(&table->mtx_print);
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->numb_philos)
	{
		pthread_mutex_destroy(&table->fork[i].mutex);
	}
	pthread_mutex_destroy(&table->mtx_meal);
	pthread_mutex_destroy(&table->mtx_end);
	pthread_mutex_destroy(&table->mtx_print);
	pthread_mutex_destroy(&table->mtx_died);
	pthread_mutex_destroy(&table->mtx_eat);
	free(table->philo);
	free(table->fork);
}

void	end_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->numb_philos)
	{
		pthread_join(table->philo[i].thread, NULL);
	}
	destroy_mutexes(table);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
