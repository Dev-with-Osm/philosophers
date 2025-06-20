/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:52:14 by okhourss          #+#    #+#             */
/*   Updated: 2025/06/19 12:52:14 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_philo philos[MAX_PHILO], pthread_mutex_t forks[MAX_PHILO],
		t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].mtx_meal);
		i++;
	}
	pthread_mutex_destroy(&args->mtx_print);
	pthread_mutex_destroy(&args->mtx_death);
}
