/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:01:17 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/21 23:47:45 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **arg)
{
	int	i;
	int	j;

	i = 1;
	while (arg[i])
	{
		j = 0;
		while (ft_isdigit(arg[i][j]))
			j++;
		if (arg[i][j] || ft_atoi(arg[i]) == -1)
			return (0);
		i++;
	}
	if (ft_atoi(arg[1]) > 200)
		return (0);
	if (ft_atoi(arg[2]) < 60 || ft_atoi(arg[3]) < 60
		|| ft_atoi(arg[4]) < 60)
		return (0);
	return (1);
}

int	check_death(t_philo philo, int flag)
{
	int			death;
	uint64_t	period;

	if (!flag)
	{
		pthread_mutex_lock(&philo.setup->deadlock);
		death = philo.setup->death;
		pthread_mutex_unlock(&philo.setup->deadlock);
		if (death || philo.meals == -1)
			return (0);
	}
	pthread_mutex_lock(&philo.mealock);
	period = get_timestamp() - philo.last_meal;
	pthread_mutex_unlock(&philo.mealock);
	if (period > (uint64_t)philo.setup->time_die)
	{
		pthread_mutex_lock(&philo.setup->deadlock);
		philo.setup->death = 1;
		pthread_mutex_unlock(&philo.setup->deadlock);
		pthread_mutex_lock(&philo.setup->wrilock);
		printf("%lld %d died\n", get_timestamp() - philo.setup->start, philo.id);
		pthread_mutex_unlock(&philo.setup->wrilock);
		return (0);
	}
	return (1);
}

int	check_meals(t_philo *philo, int j)
{
	if (philo->setup->num_meals == -1)
		return (1);
	if (j == philo->setup->num_meals )
	{
		pthread_mutex_lock(&philo->setup->deadlock);
		philo->meals = -1;
		pthread_mutex_unlock(&philo->setup->deadlock);
		usleep(100);
	}
	return (1);
}
