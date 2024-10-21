/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:38 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/21 20:16:36 by fbbot            ###   ########.fr       */
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

int	print_error(char *err)
{
	printf("%s\n", err);
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
	if (ft_atoi(argv[1]) == 0 || (argc == 6 && ft_atoi(argv[5]) == 0))
		return (0);
	setup = init_setup(argv);
	if (!setup)
		return (free_setup(setup), 1);
	forks = init_forks(*setup);
	if (!forks)
		return (free_setup(setup), free_forks(forks), 1);
	philos = NULL;
	philos = init_philos(philos, setup, forks);
	if (!philos)
		return (end_philos(philos), 1);
	if (setup->num_philos == 1)
		handle_one(philos[0]);
	end_philos(philos);
	return (0);
}
