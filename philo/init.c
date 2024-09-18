/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:50:51 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/18 22:48:58 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		setup->num_eat_times = ft_atoi(argv[5]);
	setup->start = get_timestamp();
	return (setup);
}

pthread_mutex_t	*init_forks(t_setup setup)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*tmp;
	int	i;

	forks = malloc(sizeof(pthread_mutex_t) * setup.num_philos);
	if (!forks)
		exit(print_error(ERR_MALLOC));
	i = 0;
	tmp = forks;
	while (i < setup.num_philos)
	{
		memset(&tmp[i], 0, sizeof(pthread_mutex_t));
		pthread_mutex_init(&tmp[i], NULL);
		i++;
	}
	return (forks);
}

t_philo	*init_philos(t_philo *philos, char **argv)
{
	t_philo	*tmp;
	t_setup	*setup;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write;
	pthread_mutex_t	*meal;
	int	i;

	setup = init_setup(argv);
	forks = init_forks(*setup);
	write = malloc(sizeof(pthread_mutex_t));
	meal = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(write, NULL);
	pthread_mutex_init(meal, NULL);
	philos = malloc(sizeof(t_philo) * setup->num_philos);
	if (!philos)
		exit(print_error(ERR_MALLOC));
	tmp = philos;
	i = 0;
	while (i < setup->num_philos)
	{
		tmp[i].id = i + 1;
		tmp[i].setup = setup;
		tmp[i].forks = forks;
		tmp[i].wrilock = write;
		tmp[i].mealock = meal;
		tmp[i].meals = 0;
		tmp[i].last_meal = tmp[i].setup->start;
		memset(&(tmp[i].thread), 0, sizeof(pthread_t));
		if (pthread_create(&(tmp[i].thread), NULL, living, &tmp[i]) < 0)
			exit(print_error("pthread_create error\n"));
		i++;
	}
	tmp = philos;
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_join(tmp[i].thread, NULL) < 0)
			exit(print_error("pthread_join\n"));
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
		i++;
	}
	free(philos->forks);
	pthread_mutex_destroy(philos->wrilock);
	pthread_mutex_destroy(philos->mealock);
	free(philos->wrilock);
	free(philos->mealock);
	free(philos->setup);
	free(philos);
}
