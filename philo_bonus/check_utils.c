/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:01:17 by fbbot             #+#    #+#             */
/*   Updated: 2024/11/19 15:21:49 by fbbot            ###   ########.fr       */
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
	uint64_t	period;

	if (flag)
	{
		sem_wait(philo.setup->deadlock);
		sem_post(philo.setup->deadlock);
		return (0);
	}
	sem_wait(philo.mealock);
	period = get_timestamp() - philo.last_meal;
	if (period > (uint64_t)philo.setup->time_die)
	{
		sem_post(philo.mealock);
		sem_wait(philo.setup->deadlock);
		printf("%ld ", get_timestamp() - philo.setup->start);
		printf("%d died\n", philo.id);
		exit(1);
	}
	sem_post(philo.mealock);
	return (1);
}

int	check_meals(t_philo philo, int j)
{
	if (philo.setup->num_meals == -1)
		return (1);
	if (j == philo.setup->num_meals)
		exit(0);
	return (1);
}
