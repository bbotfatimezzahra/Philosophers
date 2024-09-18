/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:38 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/18 22:48:18 by fbbot            ###   ########.fr       */
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
	return (1);
}

int	print_usage(void)
{
	printf("Usage : ./philo num_of_philos time_to_die time_to_eat");
	printf(" time_to_sleep *num_of_times_aphilo_must_eat\n");
	printf("*optional\n");
	printf("All numbers should be non null positive integers\n");
	return (0);
}

int	print_error(char *err)
{
	printf("%s\n",err);
	return (0);
}

void	print_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].setup->num_philos)
	{
		printf("Thread %d : \n",philo[i].id);
		printf("	Setup : %d %d %d %d %ld\n",philo[i].setup->num_philos, philo[i].setup->time_die, philo[i].setup->time_eat, philo[i].setup->time_sleep, philo[i].setup->start);
		i++;
	}
}

int	simulation(char **argv)
{
	t_philo	*philos;
//	int	**returns;
	int	i;
	t_philo	*tmp;
	
	philos = NULL;
	philos = init_philos(philos, argv);
	tmp = philos;
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_lock(tmp[i].mealock);
		if (get_timestamp() - tmp[i].last_meal > (uint64_t)tmp[i].setup->time_die)
		{
			pthread_mutex_lock(tmp[i].wrilock);
			printf("%ld ms %d died\n", get_timestamp() - tmp[i].setup->start, tmp[i].id);
			pthread_mutex_unlock(tmp[i].wrilock);
		}
		pthread_mutex_unlock(tmp[i].mealock);
		i++;
	}
	end_philos(philos);
/*
	i = 0;
	tmp = philos;
	returns = malloc(sizeof(int *) * ft_atoi(argv[1]));
	if (!returns)
		exit(print_error(ERR_MALLOC));
	memset(returns, 0, ft_atoi(argv[1]));
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_join(tmp[i].thread, (void **) &returns[i]) < 0)
			exit(print_error("pthread_join\n"));
		i++;
	}
	
	while (1)
	{
		while (i > ft_atoi(argv[1]))
		{
			if (returns[--i])
				end_philos(philos);
		}
	}
	
	i = 0;
	while (returns[0][i])
	{
		printf("return %d : %d\n", i+1, returns[0][i]); 
		i++;
	}
*/
	return (0);
}
	
int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (print_usage());
	if (!check_args(argv))
		return (print_usage());
	simulation(argv);
	return (0);
}
