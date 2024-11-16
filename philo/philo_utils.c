/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:02:37 by fbbot             #+#    #+#             */
/*   Updated: 2024/11/16 22:43:34 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo philo, int flag)
{
	if (!flag)
	{
		pthread_mutex_lock(&philo.setup->deadlock);
		if (philo.setup->death)
		{
			pthread_mutex_unlock(&philo.setup->deadlock);
			return (0);
		}
		pthread_mutex_unlock(&philo.setup->deadlock);
	}
	return (1);
}

void	ft_printf(char *msg, t_philo philo)
{
	pthread_mutex_lock(&philo.setup->deadlock);
	if (!philo.setup->death)
	{
		pthread_mutex_lock(&philo.setup->wrilock);
		printf(msg, get_timestamp() - philo.setup->start, philo.id);
		pthread_mutex_unlock(&philo.setup->wrilock);
		pthread_mutex_unlock(&philo.setup->deadlock);
		return ;
	}
	pthread_mutex_unlock(&philo.setup->deadlock);
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
	if (!check_death(philo, 0))
		return ;
	s = get_timestamp();
	while ((get_timestamp() - s) < (uint64_t)time)
		usleep(500);
}
