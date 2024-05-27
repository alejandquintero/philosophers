/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:32:51 by aquinter          #+#    #+#             */
/*   Updated: 2024/05/27 22:56:07 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//eat, sleep, think

bool	init_forks(t_params *params)
{
	int	i;

	params->forks = malloc(params->number_of_philos * sizeof(pthread_mutex_t));
	if (!params->forks)
	{
		printf("Something was wrong\n");
		return (false);
	}
	i = 0;
	while (i < params->number_of_philos)
	{
		if (pthread_mutex_init(&params->forks[i], NULL) != 0)
		{
			printf("Something was wrong\n");
			destroy_and_free(params, NULL);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	init_mutex_flags(t_params *params)
{
	if (pthread_mutex_init(&params->dead_mutex, NULL) != 0)
	{
		printf("Something was wrong\n");
		destroy_and_free(params, NULL);
		return (false);
	}
	if (pthread_mutex_init(&params->log_mutex, NULL) != 0)
	{
		printf("Something was wrong\n");
		destroy_and_free(params, NULL);
		return (false);
	}
	if (pthread_mutex_init(&params->meal_mutex, NULL) != 0)
	{
		printf("Something was wrong\n");
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
		philos[i].is_dead = 0;
		philos[i].is_eating = 0;
		philos[i].meals_count = 0;
		philos[i].r_fork = &params->forks[i];
		if (i == 0)
			philos[i].l_fork = &params->forks[params->number_of_philos - 1];
		else
			philos[i].l_fork = &params->forks[i - 1];
		philos[i].dead_mutex = &params->dead_mutex;
		philos[i].log_mutex = &params->log_mutex;
		philos[i].meal_mutex = &params->meal_mutex;
		philos[i].t_params = params;
		i++;
	}
}
