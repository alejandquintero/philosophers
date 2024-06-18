/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:39:17 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/18 21:12:22 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	valid_input(char *argv[])
{
	if (!is_digit(argv[1]) || ft_stol(argv[1]) <= 0 \
		|| ft_stol(argv[1]) > LONG_MAX)
		return (printf(INVALID_PHILO_NBRS), false);
	if (!is_digit(argv[2]) || ft_stol(argv[2]) <= 0 \
		|| ft_stol(argv[2]) > LONG_MAX)
		return (printf(INVALID_TIME_DIE), false);
	if (!is_digit(argv[3]) || ft_stol(argv[3]) <= 0 \
		|| ft_stol(argv[3]) > LONG_MAX)
		return (printf(INVALID_TIME_EAT), false);
	if (!is_digit(argv[4]) || ft_stol(argv[4]) <= 0 \
		|| ft_stol(argv[4]) > LONG_MAX)
		return (printf(INVALID_TIME_SLEEP), false);
	if (argv[5] && (!is_digit(argv[5]) || ft_stol(argv[5]) < 0 \
		|| ft_stol(argv[5]) > LONG_MAX))
		return (printf(INVALID_MEALS), false);
	return (true);
}

bool	get_input(char *argv[], t_params *params)
{
	if (!valid_input(argv))
		return (false);
	params->stop = false;
	params->number_of_philos = (int)ft_stol(argv[1]);
	params->time_to_die = (int)ft_stol(argv[2]);
	params->time_to_eat = (int)ft_stol(argv[3]);
	params->time_to_sleep = (int)ft_stol(argv[4]);
	if (argv[5])
		params->number_of_meals = (int)ft_stol(argv[5]);
	else
		params->number_of_meals = NO_MEAL_LIMIT;
	return (true);
}

bool	check_input(int argc, char *argv[], t_params *params)
{
	if (argc < REQUIRED_ARGUMENTS) 
		return (printf(WRONG_INPUT), false);
	if (argc > OPTIONAL_ARGUMENTS)
		return (printf(WRONG_INPUT), false);
	if (!get_input(argv, params))
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_philo		*philos;
	t_params	params;

	if (!check_input(argc, argv, &params))
		return(ERROR);
	if (!init_data(&params, &philos))
		return (printf(SYSTEM_ERROR), ERROR);
	if (!init_threads(philos, &params))
		return (printf(SYSTEM_ERROR), ERROR);
	destroy_and_free(&params, philos);
	return (SUCCESS);
}
