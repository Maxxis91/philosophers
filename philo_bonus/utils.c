/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshk <loctopus@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by jshk              #+#    #+#             */
/*   Updated: 2022/05/03 11:07:21 by jshk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int				minus;
	unsigned long	result;

	minus = 1;
	result = 0;
	while ((*str == ' ') || (*str == '\t') || (*str == '\n')
		|| (*str == '\v') || (*str == '\f') || (*str == '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + ((int)*str - '0');
		str++;
	}
	if (result > 9223372036854775807 && minus > 0)
		return (-1);
	if (result > 9223372036854775807 && minus < 0)
		return (0);
	return ((int)result * minus);
}

void	error_msg(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		error_msg("Error gettimeofday");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	mem_free(t_list *all)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_close(all->semaphore->forks);
	sem_close(all->semaphore->write_sema);
	free(all->pid);
	free(all->ar);
	free(all->semaphore);
	free(all->philo);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}
