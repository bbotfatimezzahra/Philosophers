/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:50:51 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/21 20:18:45 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_setup	*init_setup(char **argv)
{
	t_setup	*setup;

	setup = malloc(sizeof(t_setup));
	if (!setup)
		return (print_error(ERR_MALLOC), NULL);
	setup->num_philos = ft_atoi(argv[1]);
	setup->time_die = ft_atoi(argv[2]);
	setup->time_eat = ft_atoi(argv[3]);
	setup->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		setup->num_meals = ft_atoi(argv[5]);
	else
		setup->num_meals = -1;
	setup->start = get_timestamp();
	setup->death = 0;
	if (pthread_mutex_init(&setup->deadlock, NULL))
		return (print_error(ERR_MU_INIT), NULL);
	if (pthread_mutex_init(&setup->wrilock, NULL))
		return (print_error(ERR_MU_INIT), NULL);
	return (setup);
}

pthread_mutex_t	*init_forks(t_setup setup)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * setup.num_philos);
	if (!forks)
		return (print_error(ERR_MALLOC), NULL);
	i = 0;
	while (i < setup.num_philos)
	{
		memset(&forks[i], 0, sizeof(pthread_mutex_t));
		if (pthread_mutex_init(&forks[i], NULL))
			return (print_error(ERR_MU_INIT), NULL);
		i++;
	}
	return (forks);
}

t_philo	*init_philos(t_philo *philos, t_setup *setup, pthread_mutex_t *forks)
{
	int				i;

	philos = malloc(sizeof(t_philo) * setup->num_philos);
	if (!philos)
		return (print_error(ERR_MALLOC), NULL);
	i = -1;
	while (++i < setup->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].setup = setup;
		philos[i].forks = forks;
		philos[i].last_meal = philos[i].setup->start;
		philos[i].meals = 0;
		if (pthread_mutex_init(&philos[i].mealock, NULL))
			return (print_error(ERR_MU_INIT), NULL);
		memset(&philos[i].thread, 0, sizeof(pthread_t));
		if (pthread_create(&philos[i].thread, NULL, living, &philos[i]))
			return (print_error(ERR_TH_CREATE), NULL);
	}
	while (--i >= 0)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (print_error(ERR_TH_JOIN), NULL);
	}
	return (philos);
}
