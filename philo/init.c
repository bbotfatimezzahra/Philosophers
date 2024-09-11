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
		tmp[i]->id = i;
		pthread_mutex_init(&(tmp[i]->fork), NULL);
		i++;
	}
	return (forks);
}

t_setup	*init_setup(char **argv)
{
}

t_philo	*init_philos(char **argv)
{
	t_philo	*tmp;
	int	i;

	setup->philos = malloc(sizeof(t_philo) * setup->num_philos);
	if (!(setup->philos))
		exit(print_error(ERR_MALLOC));
	tmp = setup->philos;
	i = 0;
	while (i < setup->num_philos)
	{
		tmp[i].id = i + 1;
		tmp[i].times = setup->times;
		tmp[i].forks = setup->forks;
		pthread_create(&(tmp[i].thread), NULL, living, &tmp[i]);
		i++;
	}
	i = 0;
	while (i < setup->num_philos)
	{
		pthread_join(tmp[i].thread, NULL);
		i++;
	}
}
