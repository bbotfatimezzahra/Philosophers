/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:01:39 by fbbot             #+#    #+#             */
/*   Updated: 2024/11/19 12:54:19 by fbbot            ###   ########.fr       */
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
# define ERR_MUTEX_INIT "Mutex init failure"
# define ERR_MUTEX_LOCK "Mutex lock failure"
# define ERR_MUTEX_DESTROY "Mutex destroy failure"
# define ERR_THREAD_CREATE "Thread create failure"
# define ERR_THREAD_JOIN "Thread join failure"

typedef struct s_setup
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meals;
	uint64_t		start;
	int				death;
	int				meals;
	pthread_mutex_t	deadlock;
	pthread_mutex_t	wrilock;
	pthread_mutex_t	mealock;
}		t_setup;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_setup			*setup;
	pthread_mutex_t	*forks;
	uint64_t		last_meal;
}		t_philo;

int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			start_simulation(t_philo *philos, char **argv);
void			end_philos(t_philo *philos);
uint64_t		get_timestamp(void);
void			*living(void *philo);
int				print_error(char *err);
void			ft_usleep(int time, t_philo philo);
void			ft_printf(char *msg, t_philo philo);
int				check_death(t_philo philo, int flag);
t_setup			*init_setup(char **argv);
t_philo			*init_philos(t_philo *p, t_setup *s, pthread_mutex_t *f);
pthread_mutex_t	*init_forks(t_setup setup);
int				check_args(char **arg);
int				check_meals(t_philo philo, int i);
int				check_philo(t_philo philo, int *j);

#endif
