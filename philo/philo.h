/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:01:39 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/21 14:53:20 by fbbot            ###   ########.fr       */
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

# define ERR_MALLOC "Allocation Failure"
# define ERR_TH_CREATE "Thread Create Failure"
# define ERR_TH_JOIN "Thread Join Failure"
# define ERR_MU_INIT "Mutex Init Failure"
# define ERR_MU_DESTROY "Mutex Destroy Failure"

typedef struct s_setup
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meals;
	uint64_t		start;
	int				death;
	pthread_mutex_t	deadlock;
	pthread_mutex_t	wrilock;
}		t_setup;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_setup			*setup;
	pthread_mutex_t	*forks;
	uint64_t		last_meal;
	int				meals;
	pthread_mutex_t	mealock;
}		t_philo;

int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				check_args(char **arg);
int				print_error(char *err);
t_setup			*init_setup(char **argv);
pthread_mutex_t	*init_forks(t_setup setup);
t_philo			*init_philos(t_philo *p, t_setup *s, pthread_mutex_t *f);
uint64_t		get_timestamp(void);
void			ft_usleep(int time, t_philo philo);
void			*living(void *philo);
void			ft_printf(char *msg, t_philo philo);
int				check_death(t_philo philo, int flag);
int				check_meals(t_philo *philo, int i);
void			free_setup(t_setup *setup);
void			free_forks(pthread_mutex_t *forks, int num);
void			end_philos(t_philo *philos);

#endif
