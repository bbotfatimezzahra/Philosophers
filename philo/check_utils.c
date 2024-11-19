/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:01:17 by fbbot             #+#    #+#             */
/*   Updated: 2024/11/19 12:56:01 by fbbot            ###   ########.fr       */
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
		if (arg[i][j] || ft_atoi(arg[i]) == -1 || ft_atoi(arg[i]) == 0)
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
	if (!flag)
	{
		pthread_mutex_lock(&philo.setup->deadlock);
		if (philo.setup->death)
		{
			pthread_mutex_unlock(&philo.setup->deadlock);
			return (0);
		}
		pthread_mutex_unlock(&philo.setup->deadlock);
	}
	return (1);
}

int	check_meals(t_philo philo, int j)
{
	if (philo.setup->num_meals == -1)
		return (1);
	if (j == philo.setup->num_meals)
	{
		pthread_mutex_lock(&philo.setup->mealock);
		philo.setup->meals++;
		pthread_mutex_unlock(&philo.setup->mealock);
	}
	return (1);
}

int	check_philo(t_philo philo, int *j)
{
	pthread_mutex_lock(&philo.setup->mealock);
	if (philo.setup->num_philos != -1
		&& philo.setup->meals == philo.setup->num_philos)
	{
		pthread_mutex_unlock(&philo.setup->mealock);
		return (0);
	}
	if (get_timestamp() - philo.last_meal > (uint64_t)philo.setup->time_die)
	{
		pthread_mutex_unlock(&philo.setup->mealock);
		*j = 1;
		return (0);
	}
	pthread_mutex_unlock(&philo.setup->mealock);
	return (1);
}
