/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_and_lock.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelissi <gmelissi@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by gmelissi          #+#    #+#             */
/*   Updated: 2022/06/26 06:16:03 by gmelissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlocking(t_philo *ph)
{
	pthread_mutex_unlock(&ph->ar->mtx_ph[ph->left]);
	pthread_mutex_unlock(&ph->ar->mtx_ph[ph->right]);
}

void	locking(t_philo *ph)
{
	pthread_mutex_lock(&ph->ar->mtx_ph[ph->left]);
	display_info(ph, "has taken a fork");
	pthread_mutex_lock(&ph->ar->mtx_ph[ph->right]);
	display_info(ph, "has taken a fork");
}

void	destroy_threads(t_arg *ar)
{
	int	i;

	i = 0;
	while (i < ar->num_of_philo)
	{
		pthread_mutex_destroy(&ar->mtx_ph[i]);
		i++;
	}
	pthread_mutex_destroy(&ar->mtx_sig);
}

void	create_threads(t_arg *ar)
{
	int	i;

	i = -1;
	ar->when_start_dinner = get_time();
	while (++i < ar->num_of_philo)
	{
		if (!(i % 2))
			pthread_create(&ar->philo[i].ph_tread, NULL, \
			&eat_think_sleep_repeat, &ar->philo[i]);
		usleep(30);
	}
	i = -1;
	while (++i < ar->num_of_philo)
	{
		if (i % 2)
			pthread_create(&ar->philo[i].ph_tread, NULL, \
			&eat_think_sleep_repeat, &ar->philo[i]);
		usleep(30);
	}
	pthread_create(&ar->someone_died, NULL, &who_died, ar);
	pthread_join(ar->someone_died, NULL);
}
