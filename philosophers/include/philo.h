/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovack <jnovack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:06:22 by jnovack           #+#    #+#             */
/*   Updated: 2025/02/28 11:55:49 by jnovack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				philo_pick;
}					t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long int		last_meal;
	int				left_fork;
	int				right_fork;
	int				meal_count;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				numb_philos;
	int				time_to_sleep;
	int				time_to_die;
	int				time_to_eat;
	long int		start_time;
	int				end;
	int				died;
	int				someone_died;
	int				meals_needed;
	pthread_mutex_t	mtx_eat;
	pthread_mutex_t	mtx_end;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_died;
	pthread_mutex_t	mtx_meal;
	t_philo			*philo;
	t_fork			*fork;
}					t_table;

int					ft_atoi(const char *str);
long int			get_time_in_ms(void);
void				precise_sleep(long int time_in_ms, t_table *table);
void				rec_philo_action(int id, t_table *table, char *action);

int					setup_philos(t_table *table);
int					init_mutexes(t_table *table);
int					create_philos_thread(t_table *table, int i, void *routine);

// static int      init_all_mutexes(t_table *table);
// static int      validate_inputs(int argc, char **argv);
// static int      validate_number_of_arguments(int argc, char **argv);

void				destroy_mutexes(t_table *table);
void				end_table(t_table *table);
// static int      parse_arguments(int argc, t_table *table, char **argv);

int					check_philo_death(t_table *table);
void				process_philo_death(t_table *table, int i);
int					has_table_ended(t_table *table);
// static int     has_philosophers_satisfied(t_philo *philo);
// static int	pick_up_fork_mutex(t_fork *fork, t_philo *philo);

void				*philo_routine(void *philo_void);
void				*philosopher_thread(void *philo_void);
// static void	philosopher_meal(t_philo *philo);
// static void	put_down_fork_mutex(t_fork *fork);

void				monitor_death_philos(t_table *table);
void				run_table(t_table *table);
int					ft_strcmp(char *s1, char *s2);

#endif