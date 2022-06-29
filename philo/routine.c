/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelissi <gmelissi@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by gmelissi          #+#    #+#             */
/*   Updated: 2022/06/29 03:34:35 by gmelissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	time_for_eat_sleep(long ping_time)
{
	long	present_time;
	long	cut;

	present_time = get_time();
	cut = present_time + ping_time;
	while (cut > present_time)
	{
		usleep(1);
		present_time = get_time();
	}
}

static void	switch_state(t_philo *philosopher, int state)
{
	if (!state)
	{
		if (philosopher->state)
			display_info(philosopher, "is thinking");
	}
	if (state == 1)
	{
		locking(philosopher);
		philosopher->check_point_eat = get_time();
		display_info(philosopher, "is eating");
		time_for_eat_sleep(philosopher->ar->time_to_eat);
		unlocking(philosopher);
		philosopher->times_eat--;
	}
	if (state == 2)
	{
		display_info(philosopher, "is sleeping");
		time_for_eat_sleep(philosopher->ar->time_to_sleep);
	}
	philosopher->state = state;
}

void	*eat_think_sleep_repeat(void *the_philosopher)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)the_philosopher;
	pthread_detach(philosopher->ph_tread);
	philosopher->check_point_eat = philosopher->ar->when_start_dinner;
	while (1)
	{
		if (philosopher->times_eat)
		{
			switch_state(philosopher, 0);
			switch_state(philosopher, 1);
			switch_state(philosopher, 2);
			switch_state(philosopher, 0);
		}
		else
			break ;
	}
	return (NULL);
}
