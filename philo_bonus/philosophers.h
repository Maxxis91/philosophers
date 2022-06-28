/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshk <loctopus@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by jshk              #+#    #+#             */
/*   Updated: 2022/05/03 11:07:21 by jshk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>

typedef struct s_sema
{
	sem_t			*forks;
	sem_t			*check;
	sem_t			*write_sema;
}					t_sema;

typedef struct s_arg
{
	long		num_of_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		times_must_eat;
	int			death_flag;
}					t_arg;

typedef struct s_philo
{
	int				order_ph;
	long			start;
	long			last;
	t_sema			*semaphore;
	t_arg			*ar;
	pid_t			*pid;
	pthread_t		philosopher;
}					t_philo;

typedef struct s_list
{
	long			time;
	pid_t			*pid;
	t_sema			*semaphore;
	t_arg			*ar;
	t_philo			*philo;
}					t_list;

/* eat_sleep_think.c */
void	*check_death(void *philosopher);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	sleep_time(long ping);

/* go_philosophers.c */
void	go_philosopher(t_list *all);
void	wait_loop(t_list *all);
void	processing(t_philo *philo);
int		philosopher_full(t_philo *philo, int *i);

/* utils.c */
int		ft_atoi(const char *str);
void	error_msg(char *msg);
long	get_time(void);
void	mem_free(t_list *all);
int		ft_strlen(char *str);

/* init.c */
void	init_arguments(char **argv, t_list *first);
void	init_sema(t_list *all);
void	init_philosophers(t_list *all);

#endif
