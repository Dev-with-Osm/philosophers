/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:31:04 by okhourss          #+#    #+#             */
/*   Updated: 2025/06/19 14:58:40 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_log(t_philo *philo, const char *msg)
{
	t_args *args = philo->args;
	long ts;

	pthread_mutex_lock(&args->mtx_death);
	if (!args->someone_died)
	{
		pthread_mutex_lock(&args->mtx_print);
		ts = timestamp_ms() - args->start_time;
		printf("%013ld %d %s\n", ts, philo->id, msg);
		pthread_mutex_unlock(&args->mtx_print);
	}
	pthread_mutex_unlock(&args->mtx_death);
}
