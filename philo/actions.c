/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:57:05 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/18 23:13:33 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philo philo, int fork1, int fork2)
{
	pthread_mutex_lock(&(philo.forks[fork1 - 1]));
	pthread_mutex_lock(&(philo.forks[fork2 - 1]));
	pthread_mutex_lock(philo.wrilock);
	printf("%ld %d has taken a fork\n", get_timestamp() - philo.setup->start, philo.id);
	printf("%ld %d has taken a fork\n", get_timestamp() - philo.setup->start, philo.id);
	pthread_mutex_unlock(philo.wrilock);
}

void	eating(t_philo *ph)
{
	int	fork1;
	int	fork2;
	t_philo	philo;

	philo = *ph;
	fork1 = philo.id;
	fork2 = (philo.id % philo.setup->num_philos) + 1;
	if (philo.id % 2 == 0)
		grab_forks(philo, fork1, fork2);
	else
		grab_forks(philo, fork2, fork1);
	pthread_mutex_lock(philo.wrilock);
	printf("%ld %d is eating\n", get_timestamp() - philo.setup->start, philo.id);
	pthread_mutex_unlock(philo.wrilock);
	ft_usleep(philo.setup->time_eat);
	pthread_mutex_unlock(&(philo.forks[fork1 - 1]));
	pthread_mutex_unlock(&(philo.forks[fork2 - 1]));
	pthread_mutex_lock(philo.mealock);
	ph->last_meal = get_timestamp();
	ph->meals++;
	pthread_mutex_unlock(philo.mealock);
}

void	sleeping(t_philo philo)
{
	pthread_mutex_lock(philo.wrilock);
	printf("%ld %d is sleeping\n", get_timestamp() - philo.setup->start, philo.id);
	pthread_mutex_unlock(philo.wrilock);
	ft_usleep(philo.setup->time_sleep);
}

void	thinking(t_philo philo)
{
	pthread_mutex_lock(philo.wrilock);
	printf("%ld %d is thinking\n", get_timestamp() - philo.setup->start, philo.id);
	pthread_mutex_unlock(philo.wrilock);
	ft_usleep(philo.setup->time_die);
}

void	*living(void *ph)
{
	t_philo	*philo;
	int	i;

	philo = (t_philo *)ph;
	i = 1;
	while (i)
	{
		eating(philo);
		sleeping(*philo);
		thinking(*philo);
	}
	return (NULL);
}
