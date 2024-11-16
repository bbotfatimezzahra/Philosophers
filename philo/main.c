/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:38 by fbbot             #+#    #+#             */
/*   Updated: 2024/11/16 22:37:24 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_usage(void)
{
	printf("Usage : ./philo num_of_philos time_to_die time_to_eat");
	printf(" time_to_sleep *num_of_times_aphilo_must_eat\n");
	printf("*optional\n");
	printf("[0 - 200] [>60] [>60] [>60] [>=0]\n");
	return (1);
}

int	handle_one(t_philo philos)
{
	if (pthread_mutex_lock(&philos.forks[0]))
		return (print_error(ERR_MUTEX_LOCK));
	ft_printf("%ld %d has taken a fork\n", philos);
	if (pthread_mutex_unlock(&philos.forks[0]))
		return (print_error(ERR_MUTEX_LOCK));
	printf("%d 1 died\n", philos.setup->time_die);
	return (0);
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

void	monitor(t_philo *philos)
{
	int	i;
	int	j;

	while (1)
	{
		i = -1;
		while (++i < philos[0].setup->num_philos)
		{
			j = 0;
			if (!check_philo(philos[i], &j))
			{
				pthread_mutex_lock(&philos[i].setup->deadlock);
				philos->setup->death = 1;
				pthread_mutex_unlock(&philos[i].setup->deadlock);
				if (j)
				{
					pthread_mutex_lock(&philos[i].setup->wrilock);
					printf("%ld ", get_timestamp() - philos[i].setup->start);
					printf("%d died\n", philos[i].id);
					pthread_mutex_unlock(&philos[i].setup->wrilock);
				}
				return ;
			}
			usleep(100);
		}
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	t_setup			*setup;
	pthread_mutex_t	*forks;

	if (argc != 5 && argc != 6)
		return (print_usage());
	if (!check_args(argv))
		return (print_usage());
	if (ft_atoi(argv[1]) == 0)
		return (0);
	setup = init_setup(argv);
	forks = init_forks(*setup);
	philos = NULL;
	philos = init_philos(philos, setup, forks);
	if (setup->num_philos == 1)
		handle_one(philos[0]);
	else
		monitor(philos);
	end_philos(philos);
//	system("leaks philo");
	return (0);
}
