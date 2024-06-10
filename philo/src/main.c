/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:39:17 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/07 10:36:22 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	valid_input(char *argv[])
{
	if (!is_digit(argv[1]) || ft_stol(argv[1]) <= 0 \
		|| ft_stol(argv[1]) > INT_MAX)
		return (printf("Invalid philosophers numbers\n"), false);
	if (!is_digit(argv[2]) || ft_stol(argv[2]) <= 0 \
		|| ft_stol(argv[2]) > INT_MAX)
		return (printf("Invalid time to die\n"), false);
	if (!is_digit(argv[3]) || ft_stol(argv[3]) <= 0 \
		|| ft_stol(argv[3]) > INT_MAX)
		return (printf("Invalid time to eat\n"), false);
	if (!is_digit(argv[4]) || ft_stol(argv[4]) <= 0 \
		|| ft_stol(argv[4]) > INT_MAX)
		return (printf("Invalid time to sleep\n"), false);
	if (argv[5] && (!is_digit(argv[5]) || ft_stol(argv[5]) < 0 \
		|| ft_stol(argv[5]) > INT_MAX))
		return (printf("Invalid n times each philosopher must eat\n"), false);
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
		params->number_of_meals = -1;
	return (true);
}

int	main(int argc, char *argv[])
{
	t_philo 	*philos;
	t_params	params;

	if (argc != REQUIRED_ARGUMENTS && argc != OPTIONAL_ARGUMENTS)
		return (printf("Invalid arguments\n"), 1);
	if (!get_input(argv, &params))
		return (1);
	else
	{
		if (!init(&params, &philos))
			return (1);
		init_threads(philos, &params);
	}
	destroy_and_free(&params, philos);
	return (0);
}
