/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:54:54 by okhourss          #+#    #+#             */
/*   Updated: 2025/06/23 15:54:54 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	t_args *args = philo->args;

	pthread_mutex_lock(&philo->mtx_meal);
	philo->last_meal_ts = timestamp_ms();
	print_log(philo, "is eating");
	msleep_with_death_check(philo, args->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mtx_meal);
}

static void do_sleep_and_think(t_philo *philo)
{
	t_args *args = philo->args;

	print_log(philo, "is sleeping");
	msleep_with_death_check(philo, args->time_to_sleep);

	print_log(philo, "is thinking");
	// msleep_with_death_check(philo, args->time_to_sleep);
	usleep(500);
}

void *philo_routine(void *vphilo)
{
	t_philo *philo = (t_philo *)vphilo;
	t_args *args = philo->args;

	if (philo->id % 2 == 0)
		usleep(100);

	while (!is_dead(args))
	{
		if (args->num_meals >= 0)
		{
			pthread_mutex_lock(&philo->mtx_meal);
			int eaten = philo->meals_eaten;
			pthread_mutex_unlock(&philo->mtx_meal);
			if (eaten >= args->num_meals)
				break;
		}

		handle_forks(philo, 1);
		do_eat(philo);
		handle_forks(philo, 0);
		do_sleep_and_think(philo);
	}
	return (NULL);
}
