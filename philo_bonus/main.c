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

int	main(int argc, char **argv)
{
	t_list	first;

	if (argc < 5 || argc > 6)
		error_msg("Arguments must be 5 or 6");
	init_arguments(argv, &first);
	init_sema(&first);
	init_philosophers(&first);
	go_philosopher(&first);
	first.ar->death_flag = 1;
	mem_free(&first);
	return (0);
}
