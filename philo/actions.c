/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:57:05 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/11 14:34:36 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo philo, int *i)
{
	int	fork1;
	int	fork2;

	fork1 = philo.id;
	fork2 = (philo.id % philo.setup->num_philos) + 1;
	pthread_mutex_lock(&(philo.forks[fork1].fork));
	pthread_mutex_lock(&(philo.forks[fork2].fork));
	pthread_mutex_lock(&(philo.read));
	printf("%ld ms %d has taken a fork\n", get_timestamp() - philo.setup->start, philo.id);
	printf("%ld ms %d is eating\n", get_timestamp() - philo.setup->start, philo.id);
	usleep(philo.setup->time_eat);
	pthread_mutex_unlock(&(philo.read));
	pthread_mutex_unlock(&(philo.forks[fork1].fork));
	pthread_mutex_unlock(&(philo.forks[fork2].fork));
	*i = 0;
}

void	sleeping(t_philo philo)
{
	pthread_mutex_lock(&(philo.read));
	printf("%ld ms %d is sleeping\n", get_timestamp() - philo.setup->start, philo.id);
	usleep(philo.setup->time_sleep);
	pthread_mutex_unlock(&(philo.read));
}

void	thinking(t_philo philo)
{
	pthread_mutex_lock(&(philo.read));
	printf("%ld ms %d is thinking\n", get_timestamp() - philo.setup->start, philo.id);
	usleep(philo.setup->time_die);
	pthread_mutex_unlock(&(philo.read));
}

void	*living(void *ph)
{
	t_philo	*philo;
	int	i;

	philo = (t_philo *)ph;
	i = 1;
	while (i)
	{
		eating(*philo, &i);
		sleeping(*philo);
		thinking(*philo);
	}
	pthread_mutex_lock(&(philo->read));
	printf("%ld ms %d died\n", get_timestamp() - philo->setup->start, philo->id);
	pthread_mutex_unlock(&(philo->read));
	return (NULL);
}
