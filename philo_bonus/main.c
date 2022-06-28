/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelissi <gmelissi@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:21:21 by gmelissi          #+#    #+#             */
/*   Updated: 2022/06/28 21:07:49 by gmelissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_list	first;

	if (argc < 5 || argc > 6)
		error_msg("Error count arguments\n");
	init_arguments(argv, &first);
	init_sema(&first);
	init_philosophers(&first);
	go_philosopher(&first);
	first.ar->death_flag = 1;
	mem_free(&first);
	return (0);
}
