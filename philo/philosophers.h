/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelissi <gmelissi@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by gmelissi          #+#    #+#             */
/*   Updated: 2022/06/28 01:03:20 by gmelissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_arguments
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	unsigned long	when_start_dinner;
	pthread_t		someone_died;
	pthread_mutex_t	mtx_sig;
	pthread_mutex_t	*mtx_ph;
	struct s_philo	*philo;
}		t_arg;

typedef struct s_philo
{
	pthread_t			ph_tread;
	int					times_eat;
	int					left;
	int					right;
	int					order_num;
	int					state;
	unsigned long		check_point_eat;
	t_arg				*ar;
}		t_philo;

/* initialization.c */
void	init_arguments(char **argv, t_arg *ar);
void	init_mtx(t_arg *ar);
void	init_philosophers(t_arg *ar);

/* routine.c */
void	*eat_think_sleep_repeat(void *the_philosopher);
void	time_for_eat_sleep(long ping_time);

/* threads_and_lock.c */
void	create_threads(t_arg *ar);
void	destroy_threads(t_arg *ar);
void	locking(t_philo *ph);
void	unlocking(t_philo *ph);

/* who_died.c */
void	*who_died(void *ar);
int		check_life_philosopher(t_arg *ar, int i);

/* utils.c */
int		ft_atoi(const char *str);
void	error_msg(char *msg);
long	get_time(void);
void	display_info(t_philo *ph, char *str);

#endif
