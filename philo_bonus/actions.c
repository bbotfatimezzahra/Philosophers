/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:57:05 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/19 17:09:23 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philo philo)
{
	if (!check_death(philo, 0))
		return ;
	sem_wait(philo.forks);
	ft_printf("%ld %d has taken a fork\n", philo);
	sem_wait(philo.forks);
	ft_printf("%ld %d has taken a fork\n", philo);
}

void	eating(t_philo *ph, int i)
{
	t_philo	philo;

	philo = *ph;
	if (!check_death(philo, 0))
		return ;
	if (philo.id % 2 == 0)
		ft_usleep(1, philo);
	else if (philo.setup->num_philos % 2 == 1 && philo.id == 1 && !i)
			ft_usleep(philo.setup->time_eat, philo);
	grab_forks(philo);
	ft_printf("%ld %d is eating\n", philo);
	sem_wait(philo.setup->mealock);
	ph->last_meal = get_timestamp();
	sem_post(philo.setup->mealock);
	ft_usleep(philo.setup->time_eat, philo);
	sem_post(philo.forks);
	sem_post(philo.forks);
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
		eating(philo, i);
		sleeping(*philo);
		i++;
		usleep(500);
	}
}
