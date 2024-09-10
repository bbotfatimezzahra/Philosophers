/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:01:39 by fbbot             #+#    #+#             */
/*   Updated: 2024/09/10 21:06:37 by fbbot            ###   ########.fr       */
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

# define ERR_MALLOC "Allocation failure"

typedef struct s_times
{
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_eat_times;
}		t_times;

typedef struct s_philo
{
	int	id;
	pthread_t	thread;
	t_times	times;
	struct s_philo	*next;
}		t_philo;

typedef struct s_setup
{
	int	num_philos;
	t_philo	*philos;
	pthread_mutex_t	*forks;
	t_times	times;
}		t_setup;

int	ft_atoi(const char *str);
int	ft_isdigit(int c);
void	start_simulation(t_setup *setup, char **argv);
void	init_philos(t_setup *setup);
void	init_forks(t_setup *setup);
long int	get_timestamp(void);
void	*living(void *philo);
int	print_error(char *err);

#endif
