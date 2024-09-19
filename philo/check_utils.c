/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:01:17 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/19 22:49:13 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			i;

	result = 0;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = (result * 10) + (str[i++] - '0');
		if (result > INT_MAX)
			return (-1);
	}
	return (result);
}

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

int	check_meals(t_philo philo)
{
	int	i;

	if (philo.setup->num_meals == -1)
		return (1);
	pthread_mutex_lock(philo.mealock);
	if (philo.meals < philo.setup->num_meals)
		i = 1;
	else
		i = 0;
	pthread_mutex_unlock(philo.mealock);
	return (i);
}

