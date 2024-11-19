/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:01:39 by fbbot             #+#    #+#             */
/*   Updated: 2024/11/19 15:24:14 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdint.h>
# include <string.h>
# include <fcntl.h>

# define ERR_MALLOC "Allocation failure"
# define ERR_FORK "Fork Failure"
# define ERR_SEM_OPEN "Sem Open Failure"
# define ERR_SEM_CLOSE "Sem Close Failure"
# define ERR_TH_CREATE "Thread Create Failure"
# define ERR_TH_JOIN "Thread Join Failure"

typedef struct s_setup
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meals;
	uint64_t		start;
	sem_t			*wrilock;
	sem_t			*deadlock;
}		t_setup;

typedef struct s_philo
{
	int				id;
	pid_t			process;
	t_setup			*setup;
	sem_t			*forks;
	int				meals;
	uint64_t		last_meal;
	sem_t			*mealock;
}		t_philo;

int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				check_args(char **arg);
t_setup			*init_setup(char **argv);
sem_t			*init_forks(t_setup setup);
t_philo			*init_philos(t_philo *p, t_setup *s, sem_t *f);
void			print_error(char *err);
void			living(t_philo *philo);
uint64_t		get_timestamp(void);
void			ft_usleep(int time, t_philo philo);
void			ft_printf(char *msg, t_philo philo);
int				check_death(t_philo philo, int flag);
int				check_meals(t_philo philo, int i);
void			free_forks(sem_t *forks);
void			free_setup(t_setup *setup);
void			end_philos(t_philo *philos);

#endif
