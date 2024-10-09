/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:57:05 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/09 16:10:21 by fbbot            ###   ########.fr       */
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

void	eating(t_philo *ph, int i)
{
	int		fork2;
	t_philo	philo;

	philo = *ph;
	if (!check_death(philo, 0))
		return ;
	fork2 = (philo.id % philo.setup->num_philos) + 1;
	if (philo.id % 2 == 0)
	{
		ft_usleep(1, philo);
		grab_forks(philo, philo.id, fork2);
	}
	else
	{
		if (philo.setup->num_philos % 2 == 1 && philo.id == 1 && !i)
			ft_usleep(philo.setup->time_eat, philo);
		grab_forks(philo, fork2, philo.id);
	}
	ft_printf("%ld %d is eating\n", philo);
	pthread_mutex_lock(&philo.setup->mealock);
	ph->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo.setup->mealock);
	ft_usleep(philo.setup->time_eat, philo);
	pthread_mutex_unlock(&(philo.forks[philo.id - 1]));
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

void	*living(void *ph)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ph;
	if (philo->setup->num_philos == 1)
		return (NULL);
	i = 0;
	while (check_meals(*philo, i) && check_death(*philo, 0))
	{
		thinking(*philo);
		eating(philo, i);
		sleeping(*philo);
		i++;
		usleep(100);
	}
	return (NULL);
}
