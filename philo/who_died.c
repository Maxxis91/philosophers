/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who_died.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelissi <gmelissi@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by gmelissi          #+#    #+#             */
/*   Updated: 2022/06/26 06:12:34 by gmelissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_life_philosopher(t_arg *ar, int i)
{
	long	deadline;

	deadline = get_time() - ar->philo[i].check_point_eat;
	if ((int)(deadline) > ar->time_to_die)
	{
		pthread_mutex_lock(&ar->mtx_sig);
		printf("%lu %d died\n", \
				deadline, ar->philo[i].order_num);
		return (1);
	}
	return (0);
}

void	*who_died(void *ar)
{
	t_arg	*arr;
	int		i;
	int		all_ate;

	arr = (t_arg *)ar;
	while (1)
	{
		i = 0;
		all_ate = 0;
		while (i < arr->num_of_philo)
		{
			if (check_life_philosopher(arr, i))
				return (NULL);
			all_ate += arr->philo[i++].times_eat;
		}
		if (!all_ate)
		{
			pthread_mutex_lock(&arr->mtx_sig);
			return (NULL);
		}
	}
}
