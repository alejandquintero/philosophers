/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:53:26 by aquinter          #+#    #+#             */
/*   Updated: 2024/05/27 22:57:40 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_sleep(size_t ms)
{
	size_t	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < ms)
	{
		if (usleep(500) == -1)
			printf("usleep error!\n");
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		printf("gettimeofday error!\n");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
		pthread_mutex_destroy(&params->dead_mutex);
		pthread_mutex_destroy(&params->log_mutex);
		pthread_mutex_destroy(&params->meal_mutex);
	}
	if (philo)
		free(philo);
}
