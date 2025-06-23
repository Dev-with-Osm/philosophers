/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:54:18 by okhourss          #+#    #+#             */
/*   Updated: 2025/06/23 15:54:18 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_death(t_philo *p, t_args *args)
{
	long now;

	pthread_mutex_lock(&p->mtx_meal);
	now = timestamp_ms();
	if (now - p->last_meal_ts > args->time_to_die)
	{
		pthread_mutex_unlock(&p->mtx_meal);

		print_log(p, "died");

		pthread_mutex_lock(&args->mtx_death);
		args->someone_died = 1;
		pthread_mutex_unlock(&args->mtx_death);
		return (1);
	}
	pthread_mutex_unlock(&p->mtx_meal);
	return (0);
}

static int check_meals_completed(t_philo *philos, t_args *args)
{
	int i;
	int finished = 0;

	for (i = 0; i < args->num_philos; i++)
	{
		pthread_mutex_lock(&philos[i].mtx_meal);
		if (args->num_meals >= 0 && philos[i].meals_eaten >= args->num_meals)
			finished++;
		pthread_mutex_unlock(&philos[i].mtx_meal);
	}

	if (finished == args->num_philos)
	{
		pthread_mutex_lock(&args->mtx_death);
		args->someone_died = 1;
		pthread_mutex_unlock(&args->mtx_death);
		return (1);
	}
	return (0);
}

void *monitor_routine(void *vphilos)
{
	t_philo *philos = (t_philo *)vphilos;
	t_args *args = philos[0].args;
	int i;

	while (1)
	{
		pthread_mutex_lock(&args->mtx_death);
		if (args->someone_died)
		{
			pthread_mutex_unlock(&args->mtx_death);
			break;
		}
		pthread_mutex_unlock(&args->mtx_death);

		for (i = 0; i < args->num_philos; i++)
			if (check_death(&philos[i], args))
				return (NULL);

		if (args->num_meals >= 0 && check_meals_completed(philos, args))
			return (NULL);
	}
	return (NULL);
}
