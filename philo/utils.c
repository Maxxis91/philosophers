/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelissi <gmelissi@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by gmelissi          #+#    #+#             */
/*   Updated: 2022/06/26 06:08:02 by gmelissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *s)
{
	const char	*r;

	r = s;
	while (*r)
		r++;
	return (r - s);
}

int	ft_atoi(const char *src)
{
	unsigned long	res;
	int				neg;
	const char		*s;

	s = src;
	res = 0;
	neg = 0;
	while (*s && ((*s > 8 && *s < 14) || *s == 32))
		s++;
	if (*s && (*s == '+' || *s == '-'))
		if (*s++ == '-')
			neg = 1;
	while (*s && *s > 47 && *s < 58 && res < (unsigned long)LONG_MAX + 1)
		res = res * 10 + *s++ - 48;
	if ((neg && res > (unsigned long)LONG_MAX + 1) \
			|| (!neg && res > (unsigned long)LONG_MAX))
		return (neg - 1);
	if (neg)
		res *= -1;
	return ((int)res);
}

void	error_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		error_msg("Error gettimeofday\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	display_info(t_philo *ph, char *str)
{
	if (pthread_mutex_lock(&ph->ar->mtx_sig))
		error_msg("Doesn't lock display mtx!\n");
	printf("%lu %d %s\n", \
		(get_time() - ph->ar->when_start_dinner), ph->order_num, str);
	if (pthread_mutex_unlock(&ph->ar->mtx_sig))
		error_msg("Doesn't unlock display mtx!\n");
}
