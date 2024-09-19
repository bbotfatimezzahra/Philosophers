/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:50:51 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/19 22:49:14 by fbbot            ###   ########.fr       */
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
		exit(print_error(ERR_MALLOC));
	setup->num_philos = ft_atoi(argv[1]);
	setup->time_die = ft_atoi(argv[2]);
	setup->time_eat = ft_atoi(argv[3]);
	setup->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		setup->num_meals = ft_atoi(argv[5]);
	else
		setup->num_meals = -1;
	setup->start = get_timestamp();
	setup->deadlock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(setup->deadlock, NULL);
	setup->death = 0;
	return (setup);
}

pthread_mutex_t	*init_forks(t_setup setup)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * setup.num_philos);
	if (!forks)
		exit(print_error(ERR_MALLOC));
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
	pthread_mutex_t	*write;
	pthread_mutex_t	*mealock;
	int				i;

	write = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(write, NULL);
	mealock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mealock, NULL);
	philos = malloc(sizeof(t_philo) * setup->num_philos);
	if (!philos)
		exit(print_error(ERR_MALLOC));
	i = 0;
	while (i < setup->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].setup = setup;
		philos[i].forks = forks;
		philos[i].wrilock = write;
		philos[i].meals = 0;
		philos[i].last_meal = philos[i].setup->start;
		philos[i].mealock = mealock;
		memset(&philos[i].thread, 0, sizeof(pthread_t));
		pthread_create(&philos[i].thread, NULL, living, &philos[i]);
		i++;
	}
	return (philos);
}

void	end_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->setup->num_philos)
	{
		pthread_mutex_destroy(&(philos->forks[i]));
		pthread_mutex_destroy(philos[i].mealock);
		i++;
	}
	free(philos->forks);
	pthread_mutex_destroy(philos->wrilock);
	free(philos->wrilock);
	pthread_mutex_destroy(philos->setup->deadlock);
	free(philos->setup->deadlock);
	free(philos->mealock);
	free(philos->setup);
	free(philos);
}
