/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:50:51 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/11 14:34:35 by fbbot            ###   ########.fr       */
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

t_fork	*init_forks(t_setup setup)
{
	t_fork	*forks;
	t_fork	*tmp;
	int	i;

	forks = malloc(sizeof(t_fork) * setup.num_philos);
	if (!forks)
		exit(print_error(ERR_MALLOC));
	i = 0;
	tmp = forks;
	while (i < setup.num_philos)
	{
		tmp[i].id = i;
		pthread_mutex_init(&(tmp[i].fork), NULL);
		i++;
	}
	return (forks);
}

void	init_philos(t_philo *philos, char **argv)
{
	t_philo	*tmp;
	t_setup	*setup;
	t_fork	*forks;
	int	i;

	setup = init_setup(argv);
	forks = init_forks(*setup);
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
		pthread_create(&(tmp[i].thread), NULL, living, &tmp[i]);
		i++;
	}
	i = 0;
	tmp = philos;
	while (i < setup->num_philos)
		pthread_join(tmp[i++].thread, NULL);
}

void	end_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->setup->num_philos)
	{
		pthread_mutex_destroy(&(philos->forks[i].fork));
		i++;
	}
	free(philos->forks);
	free(philos->setup);
	free(philos);
}
