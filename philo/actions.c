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

void	eating(t_philo philo)
{
	//if (philo.forks[philo.id] && philo.forks[philo.id % 
	printf("%ld ms %d has taken a fork\n", get_timestamp() - philo.setup->start, philo.id);
	printf("%ld ms %d is eating\n", get_timestamp() - philo.setup->start, philo.id);
	usleep(philo.setup->time_eat);
}

void	sleeping(t_philo philo)
{
	printf("%ld ms %d is sleeping\n", get_timestamp() - philo.setup->start, philo.id);
	usleep(philo.setup->time_sleep);
}

void	thinking(t_philo philo)
{
	printf("%ld ms %d is thinking\n", get_timestamp() - philo.setup->start, philo.id);
	usleep(philo.setup->time_die);
}

void	*living(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	eating(*ph);
	sleeping(*ph);
	thinking(*ph);
	printf("%ld ms %d died\n", get_timestamp() - ph->setup->start, ph->id);
	return (NULL);
}
