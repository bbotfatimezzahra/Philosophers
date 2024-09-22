/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:57:05 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/23 00:03:30 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philo philo, int fork1, int fork2)
{
	if (!check_death(philo, 0))
		return ;
	pthread_mutex_lock(&(philo.forks[fork1 - 1]));
	ft_printf("%ld %d has taken a fork\n", philo);
	pthread_mutex_lock(&(philo.forks[fork2 - 1]));
	ft_printf("%ld %d has taken a fork\n", philo);
}

void	eating(t_philo *ph)
{
	int		fork1;
	int		fork2;
	t_philo	philo;

	philo = *ph;
	if (!check_death(philo, 0))
		return ;
	fork1 = philo.id;
	fork2 = (philo.id % philo.setup->num_philos) + 1;
	if (philo.id % 2 == 0)
		grab_forks(philo, fork1, fork2);
	else
		grab_forks(philo, fork2, fork1);
	ft_printf("%ld %d is eating\n", philo);
	pthread_mutex_lock(&philo.setup->mealock);
	ph->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo.setup->mealock);
	ft_usleep(philo.setup->time_eat, philo);
	pthread_mutex_unlock(&(philo.forks[fork1 - 1]));
	pthread_mutex_unlock(&(philo.forks[fork2 - 1]));
}

void	sleeping(t_philo philo)
{
	ft_printf("%ld %d is sleeping\n", philo);
	ft_usleep(philo.setup->time_sleep, philo);
}

void	thinking(t_philo philo)
{
	ft_printf("%ld %d is thinking\n", philo);
}

void	living(t_philo *philo)
{
	int		i;

	if (philo->setup->num_philos == 1)
		exit(0);
	i = 0;
	while (check_meals(*philo, i) && check_death(*philo, 0))
	{
		thinking(*philo);
		eating(philo);
		sleeping(*philo);
		i++;
		usleep(500);
	}
	return (NULL);
}
