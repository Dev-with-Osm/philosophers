/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:32:42 by okhourss          #+#    #+#             */
/*   Updated: 2025/06/19 14:33:55 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILO 300

typedef struct s_args
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_meals;
	long			start_time;
	bool			someone_died;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_death;
	pthread_t		monitor;
}					t_args;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_ts;
	pthread_mutex_t	mtx_meal;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_args			*args;
	pthread_t		thread;
}					t_philo;

int					ft_atoi(char *str);
int					parse_args(t_args *args, int ac, char *av[]);
int					init_sim(t_philo *philos, pthread_mutex_t forks[MAX_PHILO],
						t_args *args);
void				start_threads(t_philo philos[MAX_PHILO], t_args *args);
void				join_threads(t_philo philos[MAX_PHILO], t_args *args);
void				cleanup(t_philo philos[MAX_PHILO],
						pthread_mutex_t forks[MAX_PHILO], t_args *args);

long				timestamp_ms(void);
void				msleep_with_death_check(t_philo *philo, long ms);
void				print_log(t_philo *philo, const char *msg);

void				*philo_routine(void *vphilo);
void				*monitor_routine(void *vphilos);

#endif
