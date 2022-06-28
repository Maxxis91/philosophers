/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshk <loctopus@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by jshk              #+#    #+#             */
/*   Updated: 2022/05/03 11:07:21 by jshk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleep_time(long ping)
{
	long	present_time;
	long	cut;

	present_time = get_time();
	cut = present_time + ping;
	while (cut > present_time)
	{
		usleep(1);
		present_time = get_time();
	}
}

void	philo_think(t_philo *philo)
{
	sem_wait(philo->semaphore->write_sema);
	if (philo->ar->death_flag == 0)
		printf("time (%lu) ms - philo (%d) is thinking\n", \
		get_time() - philo->start, philo->order_ph);
	sem_post(philo->semaphore->write_sema);
}

void	philo_sleep(t_philo *philo)
{
	sem_wait(philo->semaphore->write_sema);
	if (philo->ar->death_flag == 0)
		printf("time (%lu) ms - philo (%d) is sleeping\n", \
		get_time() - philo->start, philo->order_ph);
	sem_post(philo->semaphore->write_sema);
	sleep_time(philo->ar->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->semaphore->forks);
	sem_wait(philo->semaphore->write_sema);
	if (philo->ar->death_flag == 0)
		printf("time (%lu) ms - philo (%d) is taking forks\n", \
		get_time() - philo->start, philo->order_ph);
	sem_post(philo->semaphore->write_sema);
	sem_wait(philo->semaphore->write_sema);
	if (philo->ar->death_flag == 0)
		printf("time (%lu) ms - philo (%d) is eating\n", \
		get_time() - philo->start, philo->order_ph);
	sem_post(philo->semaphore->write_sema);
	philo->last = get_time() - philo->start;
	sleep_time(philo->ar->time_to_eat);
	sem_post(philo->semaphore->forks);
}

void	*check_death(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (!philo->ar->death_flag)
	{
		sem_wait(philo->semaphore->check);
		if (get_time() - philo->start - philo->last \
		> philo->ar->time_to_die)
		{
			sem_wait(philo->semaphore->write_sema);
			printf("time (%lu) - Philo (%d) is dead\n", \
			get_time() - philo->start, philo->order_ph);
			philo->ar->death_flag = 1;
			exit (0);
		}
		sem_post(philo->semaphore->check);
	}
	return (NULL);
}
