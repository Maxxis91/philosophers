/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelissi <gmelissi@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by gmelissi          #+#    #+#             */
/*   Updated: 2022/06/28 23:14:01 by gmelissi         ###   ########.fr       */
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
	if (philo->state)
	{
		sem_wait(philo->semaphore->write_sema);
		if (!philo->ar->death_flag)
			printf("%lu %d is thinking\n", \
			get_time() - philo->start, philo->order_ph);
		sem_post(philo->semaphore->write_sema);
		philo->state = 0;
	}
}

void	philo_sleep(t_philo *philo)
{
	sem_wait(philo->semaphore->write_sema);
	if (!philo->ar->death_flag)
		printf("%lu %d is sleeping\n", \
		get_time() - philo->start, philo->order_ph);
	sem_post(philo->semaphore->write_sema);
	sleep_time(philo->ar->time_to_sleep);
	philo->state = 2;
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->semaphore->forks);
	sem_wait(philo->semaphore->write_sema);
	if (!philo->ar->death_flag)
		printf("%lu %d has taken a fork\n", \
		get_time() - philo->start, philo->order_ph);
	sem_post(philo->semaphore->write_sema);
	sem_wait(philo->semaphore->forks);
	sem_wait(philo->semaphore->write_sema);
	if (!philo->ar->death_flag)
		printf("%lu %d has taken a fork\n", \
		get_time() - philo->start, philo->order_ph);
	sem_post(philo->semaphore->write_sema);
	sem_wait(philo->semaphore->write_sema);
	if (!philo->ar->death_flag)
		printf("%lu %d is eating\n", \
		get_time() - philo->start, philo->order_ph);
	sem_post(philo->semaphore->write_sema);
	philo->last = get_time() - philo->start;
	sleep_time(philo->ar->time_to_eat);
	sem_post(philo->semaphore->forks);
	sem_post(philo->semaphore->forks);
	philo->state = 1;
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
			printf("%lu %d died\n", \
			get_time() - philo->start, philo->order_ph);
			philo->ar->death_flag = 1;
			exit (0);
		}
		sem_post(philo->semaphore->check);
	}
	return (NULL);
}
