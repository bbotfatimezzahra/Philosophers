/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:15:22 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/21 20:00:25 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_setup(t_setup *setup)
{
	if (sem_close(setup->deadlock) == -1)
		print_error(ERR_SEM_CLOSE);
	if (sem_close(setup->wrilock) == -1)
		print_error(ERR_SEM_CLOSE);
	free(setup);
}

void	free_forks(sem_t *forks)
{
	if (sem_close(forks) == -1)
		print_error(ERR_SEM_CLOSE);
}

void	end_philos(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->setup->num_philos)
	{
		if (sem_close(philos[i].mealock) == -1)
			print_error(ERR_SEM_CLOSE);
	}
	free_forks(philos->forks);
	free_setup(philos->setup);
	free(philos);
}
