/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:50:51 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/21 20:16:34 by fbbot            ###   ########.fr       */
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
	sem_unlink("write");
	setup->wrilock = sem_open("write", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("death");
	setup->deadlock = sem_open("death", O_CREAT | O_EXCL, 0644, 1);
	if (setup->wrilock == SEM_FAILED || setup->deadlock == SEM_FAILED)
		return (print_error(ERR_SEM_OPEN), NULL);
	return (setup);
}

sem_t	*init_forks(t_setup setup)
{
	sem_t	*forks;

	sem_unlink("forks");
	forks = sem_open("forks", O_CREAT | O_EXCL, 0644, setup.num_philos);
	if (forks == SEM_FAILED)
		return (print_error(ERR_SEM_OPEN), NULL);
	return (forks);
}

void	wait_philos(t_philo *philos)
{
	int	i;
	int	status;

	i = 0;
	while (i < philos->setup->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < philos->setup->num_philos)
				kill(philos[i].process, SIGKILL);
			break ;
		}
		i++;
	}
}

t_philo	*init_philos(t_philo *philos, t_setup *setup, sem_t *forks)
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
		sem_unlink("meals");
		philos[i].mealock = sem_open("meals", O_CREAT | O_EXCL, 0644, 1);
		if (philos[i].mealock == SEM_FAILED)
			return (print_error(ERR_SEM_OPEN), NULL);
		philos[i].process = fork();
		if (philos[i].process < 0)
			return (print_error(ERR_FORK), NULL);
		else if (philos[i].process == 0)
			living(&philos[i]);
	}
	wait_philos(philos);
	return (philos);
}
