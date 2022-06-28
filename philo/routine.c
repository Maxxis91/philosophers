/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelissi <gmelissi@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by gmelissi          #+#    #+#             */
/*   Updated: 2022/06/28 01:06:28 by gmelissi         ###   ########.fr       */
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
		usleep(100);
		present_time = get_time();
	}
}

static void switch_state(void *the_philosopher, int state)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)the_philosopher;
	
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
			display_info(philosopher, "is thinking");
			locking(philosopher);
			display_info(philosopher, "is eating");

			time_for_eat_sleep(philosopher->ar->time_to_eat);
			if (philosopher->times_eat > 0)
				philosopher->times_eat--;
			unlocking(philosopher);
			philosopher->check_point_eat = get_time();
			display_info(philosopher, "is sleeping");
			time_for_eat_sleep(philosopher->ar->time_to_sleep);
			display_info(philosopher, "is thinking");
		}
		else
			break ;
	}
	return (NULL);
}
