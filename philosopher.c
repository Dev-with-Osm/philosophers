/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:11:19 by okhourss          #+#    #+#             */
/*   Updated: 2025/06/19 15:00:00 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int is_dead(t_args *args)
{
	int dead;

	pthread_mutex_lock(&args->mtx_death);
	dead = args->someone_died;
	pthread_mutex_unlock(&args->mtx_death);
	return (dead);
}

static void handle_forks(t_philo *philo, int take)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;

	if (philo->id % 2 == 0)
	{
		first = philo->fork_right;
		second = philo->fork_left;
	}
	else
	{
		first = philo->fork_left;
		second = philo->fork_right;
	}
	if (take)
	{
		pthread_mutex_lock(first);
		print_log(philo, "has taken a fork");
		pthread_mutex_lock(second);
		print_log(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
	}
}

static void do_eat(t_philo *philo)
{
	t_args *args;

	args = philo->args;
	pthread_mutex_lock(&philo->mtx_meal);
	philo->last_meal_ts = timestamp_ms();
	pthread_mutex_unlock(&philo->mtx_meal);
	print_log(philo, "is eating");
	msleep_with_death_check(philo, args->time_to_eat);
	philo->meals_eaten++;
}

static void do_sleep_and_think(t_philo *philo)
{
	t_args *args;

	args = philo->args;
	print_log(philo, "is sleeping");
	msleep_with_death_check(philo, args->time_to_sleep);
	print_log(philo, "is thinking");
}

void *philo_routine(void *vphilo)
{
	t_philo *philo;
	t_args *args;

	philo = (t_philo *)vphilo;
	args = philo->args;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!is_dead(args) && (args->num_meals < 0 || philo->meals_eaten < args->num_meals))
	{
		handle_forks(philo, 1);
		do_eat(philo);
		handle_forks(philo, 0);
		do_sleep_and_think(philo);
	}
	return (NULL);
}
