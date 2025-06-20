/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:27:17 by okhourss          #+#    #+#             */
/*   Updated: 2025/06/18 11:27:17 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(t_args *args, int ac, char *av[])
{
	if (ac < 5 || ac > 6)
		return (1);
	args->num_philos = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->num_meals = -1;
	if (av[5] != NULL)
	{
		args->num_meals = ft_atoi(av[5]);
		if (args->num_meals < 0)
			return (1);
	}
	if (args->time_to_sleep <= 0 || args->time_to_eat <= 0
		|| args->time_to_die <= 0)
		return (1);
	if (args->num_philos <= 0 || args->num_philos > MAX_PHILO)
		return (1);
	args->someone_died = 0;
	pthread_mutex_init(&args->mtx_print, NULL);
	pthread_mutex_init(&args->mtx_death, NULL);
	return (0);
}
