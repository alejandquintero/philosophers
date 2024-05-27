/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:39:17 by aquinter          #+#    #+#             */
/*   Updated: 2024/05/25 23:14:47 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	ft_stol(const char *str)
{
	int		i;
	int		sign;
	long	num;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	return (num * sign);
}

bool	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 58)
			return (false);
		i++;
	}
	return (true);
}

bool	valid_input(char *argv[])
{
	if (!is_digit(argv[1]) || ft_stol(argv[1]) <= 0 || ft_stol(argv[1]) > INT_MAX)
		return(printf("Invalid philosophers numbers\n"), false);
	if (!is_digit(argv[2]) || ft_stol(argv[2]) <= 0 || ft_stol(argv[2]) > INT_MAX)
		return(printf("Invalid time to die\n"), false);
	if (!is_digit(argv[3]) || ft_stol(argv[3]) <= 0 || ft_stol(argv[3]) > INT_MAX)
		return(printf("Invalid time to eat\n"), false);
	if (!is_digit(argv[4]) || ft_stol(argv[4]) <= 0 || ft_stol(argv[4]) > INT_MAX)
		return(printf("Invalid time to sleep\n"), false);
	if (argv[5] && (!is_digit(argv[5]) || ft_stol(argv[5]) < 0 || ft_stol(argv[5]) > INT_MAX))
		return(printf("Invalid number of times each philosopher must eat\n"), false);
	return (true);
}

bool	get_input(char *argv[], t_params *params)
{
	if (!valid_input(argv))
		return (false);
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
	t_params 	params;
	size_t		start_time;

	if (argc != REQUIRED_ARGUMENTS && argc != OPTIONAL_ARGUMENTS)
		return (printf("Invalid arguments\n"), 1);
	if (!get_input(argv, &params))
		return	(1);
	else
	{
		printf("%d\n%d\n%d\n%d\n%d\n", 
			params.number_of_philos, 
			params.time_to_die, 
			params.time_to_eat,
			params.time_to_sleep,
			params.number_of_meals
		);
	
		start_time = get_current_time();
			// printf("start time %ld\n",start_time);

		printf("start\n");
		while (1)
		{
			// printf("%ld\n", get_current_time());
			ft_sleep(params.time_to_die);
			printf("%s%ld\n", CYAN, get_current_time() - start_time);
		}
	}
	return (0);
}