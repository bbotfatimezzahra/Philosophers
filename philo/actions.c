/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:57:05 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/21 15:03:20 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philo philo)
{
	int	fork1;
	int	fork2;

	if (!check_death(philo, 0))
		return ;
	fork1 = philo.id;
	fork2 = (philo.id % philo.setup->num_philos) + 1;
	pthread_mutex_lock(&(philo.forks[fork1 - 1]));
	ft_printf("%ld %d has taken a fork\n", philo);
	pthread_mutex_lock(&(philo.forks[fork2 - 1]));
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
	pthread_mutex_lock(&philo.mealock);
	ph->last_meal = get_timestamp();
	ph->meals++;
	pthread_mutex_unlock(&philo.mealock);
	ft_usleep(philo.setup->time_eat, philo);
	pthread_mutex_unlock(&(philo.forks[philo.id - 1]));
	pthread_mutex_unlock(&(philo.forks[philo.id % philo.setup->num_philos]));
	check_meals(ph, ph->meals);
}

void	sleeping_thinking(t_philo philo, int flag)
{
	if (flag)
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
	while (check_death(*philo, 0))
	{
		if (!check_death(*philo, 1))
			return (NULL);
		usleep(200);
	}
	return (ph);
}

void	*living(void *ph)
{
	t_philo		*philo;
	pthread_t	monitor;
	int			i;

	philo = (t_philo *)ph;
	if (philo->setup->num_philos == 1)
		return (NULL);
	if (pthread_create(&monitor, NULL, watch, ph))
		return (print_error(ERR_TH_CREATE), NULL);
	i = 0;
	while (check_death(*philo, 0))
	{
		sleeping_thinking(*philo, 1);
		eating(philo, i);
		sleeping_thinking(*philo, 0);
		i++;
		usleep(100);
	}
	if (pthread_join(monitor, NULL))
		return (print_error(ERR_TH_JOIN), NULL);
	return (NULL);
}
