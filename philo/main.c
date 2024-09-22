/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:38 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/22 22:48:00 by fbbot            ###   ########.fr       */
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
	pthread_mutex_lock(&philos.forks[0]);
	ft_printf("%ld %d has taken a fork\n", philos);
	pthread_mutex_unlock(&philos.forks[0]);
	printf("%d 1 died\n", philos.setup->time_die);
	return (0);
}

void	monitor(t_philo *philos)
{
	int			i;

	while (1)
	{
		i = -1;
		while (++i < philos[0].setup->num_philos)
		{
			if (!check_meals(philos[i], -1) || !check_death(philos[i], 1))
			{
				pthread_mutex_lock(&philos[i].setup->deadlock);
				philos[i].setup->death = 1;
				pthread_mutex_unlock(&philos[i].setup->deadlock);
				if (!check_death(philos[i], 1))
				{
					printf("%ld ", get_timestamp() - philos[i].setup->start);
					printf("%d died\n", philos[i].id);
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
	int				i;

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
	{
		handle_one(philos[0]);
		pthread_join(philos[0].thread, NULL);
	}
	else
	{
		monitor(philos);
		i = -1;
		while (++i < ft_atoi(argv[1]))
			pthread_join(philos[i].thread, NULL);
	}
	end_philos(philos);
	return (0);
}
