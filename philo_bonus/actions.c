/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:57:05 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/20 20:17:08 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philo philo)
{
	check_death(philo, 1);
	sem_wait(philo.forks);
	ft_printf("%ld %d has taken a fork\n", philo);
	sem_wait(philo.forks);
	ft_printf("%ld %d has taken a fork\n", philo);
}

void	eating(t_philo *ph, int i)
{
	t_philo	philo;

	philo = *ph;
	check_death(philo, 1);
	if (philo.id % 2 == 0)
		ft_usleep(1, philo);
	else if (philo.setup->num_philos % 2 == 1 && philo.id == 1 && !i)
		ft_usleep(philo.setup->time_eat, philo);
	grab_forks(philo);
	ft_printf("%ld %d is eating\n", philo);
	sem_wait(philo.mealock);
	ph->last_meal = get_timestamp();
	ph->meals++;
	sem_post(philo.mealock);
	ft_usleep(philo.setup->time_eat, philo);
	sem_post(philo.forks);
	sem_post(philo.forks);
	check_meals(*ph, ph->meals);
}

void	sleeping_thinking(t_philo philo, int flag)
{
	if (flag == 1)
		ft_printf("%ld %d is thinking\n", philo);
	else
	{
		ft_printf("%ld %d is sleeping\n", philo);
		ft_usleep(philo.setup->time_sleep, philo);
	}
}

void	*watch(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (1)
	{
		check_death(*philo, 0);
		usleep(500);
	}
	return (NULL);
}

void	living(t_philo *philo)
{
	pthread_t	monitor;
	int			i;

	if (philo->setup->num_philos == 1)
		return ;
	pthread_create(&monitor, NULL, watch, philo);
	i = 0;
	while (1)
	{
		sleeping_thinking(*philo, 1);
		eating(philo, i);
		sleeping_thinking(*philo, 2);
		i++;
		usleep(100);
	}
	pthread_join(monitor, NULL);
}
