/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:50:51 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/23 00:03:32 by fbbot            ###   ########.fr       */
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
	setup->death = 0;
	setup->meals = 0;
	return (setup);
}

sem_t	*init_forks(t_setup setup)
{
	sem_t	*forks;

	forks = sem_open("sem", O_CREAT | O_EXCL, 0644, setup.num_philos);
	if (forks == SEM_FAILED)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
	return (forks);
}

t_philo	*init_philos(t_philo *philos, t_setup *setup, sem_t *forks)
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
		philos[i].process = fork();
		if (philos[i].process < 0)
		{
			print_error(ERR_FORK);
			return (NULL);
		}
		else if (philos[i].process == 0)
			living(philo[i]);
	}
	return (philos);
}

void	end_philos(t_philo *philos)
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
				kill(philos[i].process);
			break ;
		}
		i++;
	}
	if (sem_close(philos->forks) == -1)
		print_error("Sem_close Error\n");
	free(philos->setup);
	free(philos);
}
