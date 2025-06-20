/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:16:44 by okhourss          #+#    #+#             */
/*   Updated: 2025/06/19 14:42:46 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_one_philo(t_args *args)
{
	long	start;
	long	ts;

	start = timestamp_ms();
	ts = timestamp_ms() - start;
	printf("%013ld 1 has taken a fork\n", ts);
	usleep(args->time_to_die * 1000);
	ts = timestamp_ms() - start;
	printf("%013ld 1 died\n", ts);
}

int	main(int ac, char *av[])
{
	t_args			args;
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];

	if (parse_args(&args, ac, av))
	{
		printf("Usage: %s number_of_philos time_to_die "
			"time_to_eat time_to_sleep [number_of_meals]\n",
			av[0]);
		return (1);
	}
	if (args.num_philos == 1)
	{
		handle_one_philo(&args);
		return (0);
	}
	if (init_sim(philos, forks, &args))
	{
		printf("Initialization failed.\n");
		return (1);
	}
	start_threads(philos, &args);
	join_threads(philos, &args);
	cleanup(philos, forks, &args);
	return (0);
}
