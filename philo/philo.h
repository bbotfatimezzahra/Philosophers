/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:01:39 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/18 22:46:51 by fbbot            ###   ########.fr       */
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
# include <string.h>

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

typedef struct s_philo
{
	int	id;
	pthread_t	thread;
	t_setup	*setup;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*wrilock;
	pthread_mutex_t	*mealock;
	int	meals;
	uint64_t	last_meal;
}		t_philo;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);
void	start_simulation(t_philo *philos, char **argv);
t_philo	*init_philos(t_philo *philos, char **argv);
void	end_philos(t_philo *philos);
uint64_t	get_timestamp(void);
void	*living(void *philo);
int	print_error(char *err);
void	ft_usleep(int	time);

#endif
