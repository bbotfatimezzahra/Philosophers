/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:48:17 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/11 14:34:39 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_simulation(t_philo *philos, char **argv)
{
	setup->num_philos = ft_atoi(argv[1]);
	setup->times.time_die = ft_atoi(argv[2]);
	setup->times.time_eat = ft_atoi(argv[3]);
	setup->times.time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		setup->times.num_eat_times = ft_atoi(argv[5]);
	setup->times.start = get_timestamp();
	init_philos(setup);
	init_forks(setup);
}

void	end_simulation(t_setup *setup)
{
	int	i;

	i = 0;
	while (i < setup->num_philos)
	{
		pthread_mutex_destroy(&(setup->forks[i].fork));
		i++;
	}
	free(setup->forks);
	setup->forks = NULL;
	free(setup->philos);
	setup->philos = NULL;
}

void	start_simulation(t_setup *setup, char **argv)
{
	init_simulation(setup, argv);
	printf("simulation started\n");
	end_simulation(setup);
}
