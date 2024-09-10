/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:50:51 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/10 21:07:46 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_setup *setup)
{
	int	i;

	setup->forks = malloc(sizeof(pthread_mutex_t) * setup->num_philos);
	if (!setup->forks)
		exit(print_error(ERR_MALLOC));
	i = 0;
	while (i < setup->num_philos)
	{
		pthread_mutex_init(&(setup->forks[i]), NULL);
		i++;
	}
}

void	init_philos(t_setup *setup)
{
	t_philo	*tmp;
	int	i;

	setup->philos = malloc(sizeof(t_philo) * setup->num_philos);
	if (!(setup->philos))
		exit(print_error(ERR_MALLOC));
	tmp = setup->philos;
	i = 1;
	while (tmp)
	{
		tmp->id = i;
		tmp->times = setup->times;
		pthread_create(&(tmp->thread), NULL, living, tmp);
		pthread_join(tmp->thread, NULL);
		i++;
		tmp = tmp->next;
	}
}
