/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:32:51 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/19 22:33:34 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	init_forks(t_params *params)
{
	int	i;

	i = 0;
	params->forks = malloc(params->number_of_philos * sizeof(pthread_mutex_t));
	if (!params->forks)
		return (false);
	while (i < params->number_of_philos)
	{
		if (pthread_mutex_init(&params->forks[i], NULL) != 0)
		{
			destroy_and_free(params, NULL);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	init_mutex_flags(t_params *params)
{
	if (pthread_mutex_init(&params->stop_mutex, NULL) != 0)
	{
		destroy_and_free(params, NULL);
		return (false);
	}
	if (pthread_mutex_init(&params->log_mutex, NULL) != 0)
	{
		destroy_and_free(params, NULL);
		return (false);
	}
	if (pthread_mutex_init(&params->meal_mutex, NULL) != 0)
	{
		destroy_and_free(params, NULL);
		return (false);
	}
	return (true);
}

void	init_philos(t_params *params, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < params->number_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].is_eating = false;
		philos[i].meals_count = 0;
		philos[i].right_fork = &params->forks[i];
		if (i == 0)
			philos[i].left_fork = &params->forks[params->number_of_philos - 1];
		else
			philos[i].left_fork = &params->forks[i - 1];
		philos[i].start_time = get_time();
		philos[i].last_meal_time = get_time();
		philos[i].stop_mutex = &params->stop_mutex;
		philos[i].log_mutex = &params->log_mutex;
		philos[i].meal_mutex = &params->meal_mutex;
		philos[i].params = params;
		i++;
	}
}

bool	init_data(t_params *params, t_philo **philos)
{
	*philos = NULL;
	if (!init_forks(params))
		return (false);
	if (!init_mutex_flags(params))
		return (false);
	*philos = malloc(params->number_of_philos * sizeof(t_philo));
	if (!*philos)
	{
		destroy_and_free(params, NULL);
		return (false);
	}
	init_philos(params, *philos);
	return (true);
}
