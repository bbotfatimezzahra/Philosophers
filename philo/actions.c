/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:57:05 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/10 19:08:48 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo philo)
{
	printf("%ld ms %d has taken a fork\n", get_timestamp(), philo.id);
	printf("%ld ms %d is eating\n", get_timestamp(), philo.id);
	usleep(philo.times.time_eat);
}

void	sleeping(t_philo philo)
{
	printf("%ld ms %d is sleeping\n", get_timestamp(), philo.id);
	usleep(philo.times.time_sleep);
}

void	thinking(t_philo philo)
{
	printf("%ld ms %d is thinking\n", get_timestamp(), philo.id);
	usleep(philo.times.time_die);
}

void	*living(void *philo)
{
	eating(*(t_philo *)philo);
	sleeping(*(t_philo *)philo);
	thinking(*(t_philo *)philo);
	printf("%ld ms %d died\n", get_timestamp(), (*(t_philo *)philo).id);
	return (NULL);
}
