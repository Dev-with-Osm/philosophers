/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:12:17 by okhourss          #+#    #+#             */
/*   Updated: 2025/06/19 14:30:00 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

long	timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	msleep_with_death_check(t_philo *philo, long ms)
{
	long	start;
	int		dead;

	start = timestamp_ms();
	while (1)
	{
		pthread_mutex_lock(&philo->args->mtx_death);
		dead = philo->args->someone_died;
		pthread_mutex_unlock(&philo->args->mtx_death);
		if (dead)
			break ;
		if (timestamp_ms() - start >= ms)
			break ;
		usleep(100);
	}
}
