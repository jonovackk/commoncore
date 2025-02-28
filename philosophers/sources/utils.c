/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:54:59 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/28 12:04:47 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/custom_letters.h"
#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (sign == 1 && result > INT_MAX)
			return (-1);
		if (sign == -1 && (-result) < INT_MIN)
			return (-1);
		str++;
	}
	return ((int)(result * sign));
}

long int	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(long int time_in_ms, t_table *table)
{
	long int	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < time_in_ms)
	{
		if (check_philo_death(table))
			break ;
		if (has_table_ended(table))
			break ;
		usleep(100);
	}
}

void	rec_philo_action(int id, t_table *table, char *action)
{
	pthread_mutex_lock(&(table->mtx_print));
	if (!check_philo_death(table) && !has_table_ended(table))
	{
		printf(COLOR_CYAN "%4zi " COLOR_DEFAULT, get_time_in_ms() - table->start_time);
		if (ft_strcmp(action, "has taken a fork.") == 0)
			printf(BOLD_WHITE "%d " BOLD_GREEN "%-18s %s\n" COLOR_DEFAULT, id, action, "🍽️");
		else if (ft_strcmp(action, "is eating.") == 0)
			printf(BOLD_WHITE "%d " BOLD_BLUE "%-18s %s\n" COLOR_DEFAULT, id, action, "🥘");
		else if (ft_strcmp(action, "is sleeping.") == 0)
			printf(BOLD_WHITE "%d " BOLD_PURPLE "%-18s %s\n" COLOR_DEFAULT, id, action, "💤");
		else if (ft_strcmp(action, "is thinking.") == 0)
			printf(BOLD_WHITE "%d " BOLD_CYAN "%-18s %s\n" COLOR_DEFAULT, id, action, "🤔");
		else if (ft_strcmp(action, "died.") == 0)
			printf(COLOR_RED "%d %s %14s\n" COLOR_DEFAULT, id, action, "☠️");
		else
			printf("%d %s\n", id, action);
	}
	pthread_mutex_unlock(&(table->mtx_print));
}
