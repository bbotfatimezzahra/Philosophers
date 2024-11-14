/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:50:51 by fbbot             #+#    #+#             */
/*   Updated: 2024/11/14 10:48:41 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *err)
{
	printf("%s\n", err);
	return (1);
}

t_setup	*init_setup(char **argv)
{
	t_setup	*setup;

	setup = malloc(sizeof(t_setup));
	if (!setup)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
	setup->num_philos = ft_atoi(argv[1]);
	setup->time_die = ft_atoi(argv[2]);
	setup->time_eat = ft_atoi(argv[3]);
	setup->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		setup->num_meals = ft_atoi(argv[5]);
	else
		setup->num_meals = -1;
	setup->start = get_timestamp();
	pthread_mutex_init(&setup->deadlock, NULL);
	pthread_mutex_init(&setup->mealock, NULL);
	pthread_mutex_init(&setup->wrilock, NULL);
	setup->death = 0;
	setup->meals = 0;
	return (setup);
}

pthread_mutex_t	*init_forks(t_setup setup)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * setup.num_philos);
	if (!forks)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
	i = 0;
	while (i < setup.num_philos)
	{
		memset(&forks[i], 0, sizeof(pthread_mutex_t));
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo	*init_philos(t_philo *philos, t_setup *setup, pthread_mutex_t *forks)
{
	int				i;

	philos = malloc(sizeof(t_philo) * setup->num_philos);
	if (!philos)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
	i = -1;
	while (++i < setup->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].setup = setup;
		philos[i].forks = forks;
		philos[i].last_meal = philos[i].setup->start;
		memset(&philos[i].thread, 0, sizeof(pthread_t));
		pthread_create(&philos[i].thread, NULL, living, &philos[i]);
	}
	return (philos);
}

void	end_philos(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].setup->num_philos)
		pthread_join(philos[i].thread, NULL);
	i = 0;
	while (i < philos->setup->num_philos)
	{
		pthread_mutex_destroy(&(philos->forks[i]));
		i++;
	}
	free(philos->forks);
	pthread_mutex_destroy(&philos->setup->mealock);
	pthread_mutex_destroy(&philos->setup->wrilock);
	pthread_mutex_destroy(&philos->setup->deadlock);
	free(philos->setup);
	free(philos);
}
