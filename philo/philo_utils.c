/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:02:37 by fbbot             #+#    #+#             */
/*   Updated: 2024/11/19 23:26:47 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
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

void	ft_printf(char *msg, t_philo philo)
{
	pthread_mutex_lock(&philo.setup->deadlock);
	if (!philo.setup->death)
	{
		pthread_mutex_lock(&philo.setup->wrilock);
		printf(msg, get_timestamp() - philo.setup->start, philo.id);
		pthread_mutex_unlock(&philo.setup->wrilock);
		pthread_mutex_unlock(&philo.setup->deadlock);
		return ;
	}
	pthread_mutex_unlock(&philo.setup->deadlock);
}

uint64_t	get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

void	ft_usleep(int time, t_philo philo)
{
	uint64_t	s;

	if (!check_death(philo, 0))
		return ;
	s = get_timestamp();
	while (check_death(philo, 0) && ((get_timestamp() - s) < (uint64_t)time))
		usleep(50);
}
