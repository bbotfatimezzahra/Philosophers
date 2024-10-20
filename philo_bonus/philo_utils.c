/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:02:37 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/20 20:15:13 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo philo, int flag)
{
	uint64_t	period;

	if (flag)
	{
		sem_wait(philo.setup->deadlock);
		sem_post(philo.setup->deadlock);
		return (0);
	}
	sem_wait(philo.mealock);
	period = get_timestamp() - philo.last_meal;
	sem_post(philo.mealock);
	if (period > (uint64_t)philo.setup->time_die)
	{
		sem_wait(philo.setup->deadlock);
		printf("%lld ", get_timestamp() - philo.setup->start);
		printf("%d died\n", philo.id);
		exit(1);
	}
	return (1);
}

void	ft_printf(char *msg, t_philo philo)
{
	check_death(philo, 1);
	sem_wait(philo.setup->wrilock);
	printf(msg, get_timestamp() - philo.setup->start, philo.id);
	sem_post(philo.setup->wrilock);
}

uint64_t	get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

void	ft_usleep(int time, t_philo philo)
{
	uint64_t	s;

	check_death(philo, 1);
	s = get_timestamp();
	while ((get_timestamp() - s) < (uint64_t)time)
		usleep(500);
}
