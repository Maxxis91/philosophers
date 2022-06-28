/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshk <loctopus@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by jshk              #+#    #+#             */
/*   Updated: 2022/05/03 11:07:21 by jshk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_arguments(char **argv, t_list *first)
{
	first->ar = (t_arg *)malloc(sizeof(t_arg));
	if (!first->ar)
		error_msg("malloc error!");
	first->ar->num_of_philo = ft_atoi(argv[1]);
	first->ar->time_to_die = ft_atoi(argv[2]);
	first->ar->time_to_eat = ft_atoi(argv[3]);
	first->ar->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		first->ar->times_must_eat = ft_atoi(argv[5]);
		if (first->ar->times_must_eat < 1
			|| first->ar->times_must_eat == __INT_MAX__)
			error_msg("Invalid arguments");
	}
	else
		first->ar->times_must_eat = 0;
	if (first->ar->num_of_philo < 1 || first->ar->time_to_die < 1
		|| first->ar->time_to_eat < 1 || first->ar->time_to_sleep < 1)
		error_msg("Invalid Arguments");
	first->ar->death_flag = 0;
}

void	init_sema(t_list *all)
{
	all->semaphore = (t_sema *)malloc(sizeof(t_sema));
	if (!all->semaphore)
		error_msg("malloc error!");
	sem_unlink("write");
	sem_unlink("check");
	all->semaphore->write_sema = sem_open("write", O_CREAT, 0644, 1);
	all->semaphore->check = sem_open("check", O_CREAT, 0644, 1);
	if (all->semaphore->write_sema == SEM_FAILED)
		error_msg("Semaphore doesn't create");
	sem_unlink("forks");
	all->semaphore->forks = sem_open("forks", \
	O_CREAT, 0644, all->ar->num_of_philo / 2);
	if (all->semaphore->forks == SEM_FAILED)
		error_msg("Fork doesn't create");
}

void	init_philosophers(t_list *all)
{
	long	when_dinner_start;

	when_dinner_start = get_time();
	all->philo = (t_philo *)malloc(sizeof(t_philo));
	if (!all->philo)
		error_msg("malloc error!");
	all->pid = (pid_t *)malloc(sizeof(pid_t) \
	* all->ar->num_of_philo);
	if (!all->pid)
		error_msg("malloc error!");
	all->philo->start = when_dinner_start;
	all->philo->pid = all->pid;
	all->philo->ar = all->ar;
	all->philo->semaphore = all->semaphore;
	all->philo->last = 0;
}
