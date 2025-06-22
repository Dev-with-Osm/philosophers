/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:12:38 by okhourss          #+#    #+#             */
/*   Updated: 2025/06/22 13:12:38 by okhourss         ###   ########.fr       */
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
		pthread_mutex_lock(&args->mtx_death);
		args->someone_died = 1;
		pthread_mutex_unlock(&args->mtx_death);
		print_log(p, "died");
		return (1);
	}
	pthread_mutex_unlock(&p->mtx_meal);
	return (0);
}

static int check_meals_completed(t_philo *philos, t_args *args)
{
	int i;
	int finished = 0;

	i = 0;
	while (i < args->num_philos)
	{
		pthread_mutex_lock(&philos[i].mtx_meal);
		if (args->num_meals >= 0 && philos[i].meals_eaten >= args->num_meals)
			finished++;
		pthread_mutex_unlock(&philos[i].mtx_meal);
		i++;
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
		int died = args->someone_died;
		pthread_mutex_unlock(&args->mtx_death);
		if (died)
			break;

		i = 0;
		while (i < args->num_philos)
		{
			if (check_death(&philos[i], args))
				return (NULL);
			i++;
		}
		if (args->num_meals >= 0 && check_meals_completed(philos, args))
			return (NULL);
	}
	return (NULL);
}
