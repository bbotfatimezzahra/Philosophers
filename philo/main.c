/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:38 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/19 22:49:12 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_usage(void)
{
	write(2, "Error\n", 6);
	printf("Usage : ./philo num_of_philos time_to_die time_to_eat");
	printf(" time_to_sleep *num_of_times_aphilo_must_eat\n");
	printf("*optional\n");
	printf("All numbers should be non null positive integers\n");
	return (1);
}

void	monitor(t_philo *philos)
{
	int			i;
	uint64_t	period;

	while (1)
	{
		i = 0;
		while (i < philos[0].setup->num_philos)
		{
			pthread_mutex_lock(philos[i].mealock);
			period = get_timestamp() - philos[i].last_meal;
			if (period > (uint64_t)philos[i].setup->time_die)
			{
				pthread_mutex_unlock(philos[i].mealock);
				pthread_mutex_lock(philos[i].setup->deadlock);
				philos[i].setup->death = 1;
				pthread_mutex_unlock(philos[i].setup->deadlock);
				printf("%ld %d died\n", (get_timestamp()
				- philos[i].setup->start), philos[i].id);
				end_philos(philos);
				exit(0);
			}
			pthread_mutex_unlock(philos[i].mealock);
			i++;
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
	monitor(philos);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_join(philos[i].thread, NULL) < 0)
			exit(print_error("pthread_join\n"));
		i++;
	}
	end_philos(philos);
	return (0);
}
