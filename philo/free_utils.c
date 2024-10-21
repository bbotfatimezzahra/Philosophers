/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:09:50 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/21 15:56:14 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_setup(t_setup *setup)
{
	if (pthread_mutex_destroy(&setup->wrilock))
	{
		printf("setup write\n");
		print_error(ERR_MU_DESTROY);
		return ;
	}
	if (pthread_mutex_destroy(&setup->deadlock))
	{
		printf("setup dead\n");
		print_error(ERR_MU_DESTROY);
		return ;
	}
	free(setup);
}

void	free_forks(pthread_mutex_t *forks, int num)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		if (pthread_mutex_destroy(&(forks[i])))
		{
			printf("forks\n");
			print_error(ERR_MU_DESTROY);
			return ;
		}
	}
	free(forks);
}

void	end_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->setup->num_philos)
	{
		if (pthread_mutex_destroy(&philos[i].mealock))
		{
			printf("philo meal\n");
			print_error(ERR_MU_DESTROY);
			return ;
		}
		i++;
	}
	free_forks(philos->forks, philos->setup->num_philos);
	free_setup(philos->setup);
	free(philos);
}
