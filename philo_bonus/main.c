/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:38 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/20 20:24:17 by fbbot            ###   ########.fr       */
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
	sem_wait(philos.forks);
	ft_printf("%ld %d has taken a fork\n", philos);
	sem_post(philos.forks);
	printf("%d 1 died\n", philos.setup->time_die);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	t_setup			*setup;
	sem_t			*forks;

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
	end_philos(philos);
	return (0);
}
