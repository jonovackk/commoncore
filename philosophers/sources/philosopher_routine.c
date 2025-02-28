/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:56:56 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/21 17:56:56 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	rec_philo_action(philo->id, philo->table, "has taken a fork.");
	usleep(philo->table->time_to_die * 1000);
	rec_philo_action(philo->id, philo->table, "died.");
	return (NULL);
}

static int	pick_up_fork_mutex(t_fork *fork, t_philo *philo)
{
	pthread_mutex_lock(&fork->mutex);
	if (!fork->philo_pick)
	{
		rec_philo_action(philo->id, philo->table, "has taken a fork.");
		fork->philo_pick = philo->id;
	}
	if (fork->philo_pick == philo->id)
	{
		pthread_mutex_unlock(&fork->mutex);
		return (1);
	}
	pthread_mutex_unlock(&fork->mutex);
	return (0);
}

static void	put_down_fork_mutex(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->philo_pick = 0;
	pthread_mutex_unlock(&fork->mutex);
}

static void	philosopher_meal(t_philo *philo)
{
	while (1)
	{
		if (pick_up_fork_mutex(&philo->table->fork[philo->left_fork], philo))
			break ;
		usleep(100);
	}
	while (1)
	{
		if (pick_up_fork_mutex(&philo->table->fork[philo->right_fork], philo))
			break ;
		usleep(100);
	}
	pthread_mutex_lock(&philo->table->mtx_meal);
	rec_philo_action(philo->id, philo->table, "is eating.");
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->table->mtx_meal);
	precise_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->table->mtx_eat);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->table->mtx_eat);
	put_down_fork_mutex(&philo->table->fork[philo->left_fork]);
	put_down_fork_mutex(&philo->table->fork[philo->right_fork]);
}

void	*philosopher_thread(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if (philo->id % 2 == 0)
		usleep(1500);
	while (!check_philo_death(philo->table))
	{
		philosopher_meal(philo);
		if (has_table_ended(philo->table))
			break ;
		rec_philo_action(philo->id, philo->table, "is sleeping.");
		precise_sleep(philo->table->time_to_sleep, philo->table);
		rec_philo_action(philo->id, philo->table, "is thinking.");
	}
	return (NULL);
}
