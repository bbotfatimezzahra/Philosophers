/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:01:39 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/11 14:34:37 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# include <stdint.h>

# define ERR_MALLOC "Allocation failure"

typedef struct s_setup
{
	int	num_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_eat_times;
	uint64_t	start;
}		t_setup;

typedef struct s_fork
{
	int	id;
	pthread_mutex_t	fork;
}		t_fork;

typedef struct s_philo
{
	int	id;
	pthread_t	thread;
	t_setup	*setup;
	t_fork	*forks;
	pthread_mutex_t	read;
	pthread_mutex_t	write;
}		t_philo;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);
void	start_simulation(t_philo *philos, char **argv);
t_philo	*init_philos(t_philo *philos, char **argv);
void	end_philos(t_philo *philos);
uint64_t	get_timestamp(void);
void	*living(void *philo);
int	print_error(char *err);

#endif
