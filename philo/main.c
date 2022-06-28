/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelissi <gmelissi@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by gmelissi          #+#    #+#             */
/*   Updated: 2022/06/26 06:08:48 by gmelissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_arg	ar;

	if (argc < 5 || argc > 6)
		error_msg("Error count arguments\n");
	init_arguments(argv, &ar);
	init_mtx(&ar);
	init_philosophers(&ar);
	create_threads(&ar);
	destroy_threads(&ar);
	free(ar.philo);
	free(ar.mtx_ph);
	return (0);
}
