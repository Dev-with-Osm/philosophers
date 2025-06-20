/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:55:04 by okhourss          #+#    #+#             */
/*   Updated: 2025/06/18 12:55:04 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_philo philos[MAX_PHILO], t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_philos)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	pthread_create(&args->monitor, NULL, monitor_routine, philos);
}

void	join_threads(t_philo philos[MAX_PHILO], t_args *args)
{
	int	i;

	pthread_join(args->monitor, NULL);
	i = 0;
	while (i < args->num_philos)
		pthread_join(philos[i++].thread, NULL);
}
