/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:10:29 by okhourss          #+#    #+#             */
/*   Updated: 2025/06/18 12:10:29 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_sim(t_philo *philos, pthread_mutex_t forks[MAX_PHILO], t_args *args)
{
	int	i;

	args->start_time = timestamp_ms();
	i = 0;
	while (i < args->num_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < args->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_ts = args->start_time;
		philos[i].args = args;
		philos[i].fork_left = &forks[i];
		philos[i].fork_right = &forks[(i + 1) % args->num_philos];
		if (pthread_mutex_init(&philos[i].mtx_meal, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
