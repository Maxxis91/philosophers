/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelissi <gmelissi@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by gmelissi          #+#    #+#             */
/*   Updated: 2022/06/28 01:05:42 by gmelissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mtx(t_arg *ar)
{
	int	i;

	i = -1;
	pthread_mutex_init(&ar->mtx_sig, NULL);
	while (++i < ar->num_of_philo)
		pthread_mutex_init(&ar->mtx_ph[i], NULL);
}

void	init_arguments(char **argv, t_arg *ar)
{
	ar->num_of_philo = ft_atoi(argv[1]);
	ar->time_to_die = ft_atoi(argv[2]);
	ar->time_to_eat = ft_atoi(argv[3]);
	ar->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		ar->times_must_eat = ft_atoi(argv[5]);
		if (ar->times_must_eat < 1)
			error_msg("Error: invalid arguments\n");
	}
	else
		ar->times_must_eat = -42;
	if (ar->num_of_philo < 1 || ar->time_to_die < 1 || ar->time_to_eat < 1
		|| ar->time_to_sleep < 1)
		error_msg("Error: invalid arguments\n");
	ar->philo = malloc(sizeof (t_philo) * ar->num_of_philo);
	if (!ar->philo)
		error_msg("Error in philo malloc\n");
	ar->mtx_ph = malloc(sizeof(pthread_mutex_t) * ar->num_of_philo);
	if (!ar->mtx_ph)
		error_msg("Error in mutex malloc\n");
}

void	init_philosophers(t_arg *ar)
{
	int	i;

	i = -1;
	while (++i < ar->num_of_philo)
	{
		ar->philo[i].order_num = i + 1;
		ar->philo[i].times_eat = ar->times_must_eat;
		ar->philo[i].left = i;
		ar->philo[i].ar = ar;
		if (i < ar->num_of_philo - 1)
			ar->philo[i].right = (i + 1);
		ar->philo[i].state = -1;
	}
	if (ar->num_of_philo != 1)
		ar->philo[--i].right = 0;
	if (ar->num_of_philo == 1)
		ar->philo[0].right = 0;
}
