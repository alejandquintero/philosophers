/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:39:17 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/19 21:57:27 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char *argv[])
{
	t_philo		*philos;
	t_params	params;

	if (!check_input(argc, argv, &params))
		return (ERROR);
	if (!init_data(&params, &philos))
		return (printf(SYSTEM_ERROR), ERROR);
	if (!init_threads(philos, &params))
		return (printf(SYSTEM_ERROR), ERROR);
	destroy_and_free(&params, philos);
	return (SUCCESS);
}
