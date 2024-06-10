/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:47:36 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/07 10:37:32 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	destroy_and_free(t_params *params, t_philo *philo)
{
	int	i;

	i = 0;
	if (params)
	{
		if (params->forks)
		{
			while (i < params->number_of_philos)
			{
				pthread_mutex_destroy(&params->forks[i]);
				i++;
			}
			free(params->forks);
		}
		pthread_mutex_destroy(&params->stop_mutex);
		pthread_mutex_destroy(&params->log_mutex);
		pthread_mutex_destroy(&params->meal_mutex);
	}
	if (philo)
		free(philo);
}
