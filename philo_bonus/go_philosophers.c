/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelissi <gmelissi@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by gmelissi          #+#    #+#             */
/*   Updated: 2022/06/28 23:06:05 by gmelissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philosopher_full(t_philo *philo, int *i)
{
	if (philo->ar->times_must_eat > 0)
	{
		(*i)++;
		if (*i == philo->ar->times_must_eat)
			exit (1);
	}
	return (0);
}

void	processing(t_philo *philo)
{
	int			i;
	pthread_t	death_thread;

	i = 0;
	pthread_create(&death_thread, NULL, check_death, (void *)philo);
	pthread_detach(death_thread);
	while (!philo->ar->death_flag)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (philosopher_full(philo, &i))
			exit (0);
	}
}

void	wait_loop(t_list *all)
{
	int	i;
	int	j;
	int	state;

	i = 0;
	while (i < all->ar->num_of_philo)
	{
		waitpid(-1, &state, 0);
		if (state == 0)
		{
			j = 0;
			while (j < all->ar->num_of_philo)
			{
				kill(all->philo->pid[j], SIGTERM);
				j++;
			}
		}
		i++;
	}
}

void	go_philosopher(t_list *all)
{
	int	i;

	i = 0;
	while (i < all->ar->num_of_philo)
	{
		all->philo->pid[i] = fork();
		if (all->philo->pid[i] == 0)
		{
			all->philo->order_ph = i + 1;
			all->philo->state = -1;
			processing(all->philo);
		}
		else if (all->philo->pid[i] == -1)
			error_msg("Error forking procs\n");
		i++;
	}
	wait_loop(all);
}
