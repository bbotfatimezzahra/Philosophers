/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:01:39 by fbbot             #+#    #+#             */
/*   Updated: 2024/10/20 20:23:03 by fbbot            ###   ########.fr       */
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
# define ERR_FORK "Fork failure"
# define ERR_SEM "Sem failure"

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
void			start_simulation(t_philo *philos, char **argv);
void			end_philos(t_philo *philos);
uint64_t		get_timestamp(void);
void			living(t_philo *philo);
int				print_error(char *err);
void			ft_usleep(int time, t_philo philo);
void			ft_printf(char *msg, t_philo philo);
int				check_death(t_philo philo, int flag);
t_setup			*init_setup(char **argv);
t_philo			*init_philos(t_philo *p, t_setup *s, sem_t *f);
sem_t			*init_forks(t_setup setup);
int				check_args(char **arg);
int				check_meals(t_philo philo, int i);

#endif
