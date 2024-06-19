/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:50:59 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/19 22:33:34 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	loop(t_philo *philo)
{
	pthread_mutex_lock(philo->stop_mutex);
	if (philo->params->stop)
	{
		pthread_mutex_unlock(philo->stop_mutex);
		return (false);
	}
	pthread_mutex_unlock(philo->stop_mutex);
	return (true);
}

bool	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (false);
	print(EATING, philo);
	pthread_mutex_lock(philo->meal_mutex);
	philo->is_eating = true;
	philo->last_meal_time = get_time();
	philo->meals_count++;
	pthread_mutex_unlock(philo->meal_mutex);
	ft_usleep(philo->params->time_to_eat);
	pthread_mutex_lock(philo->meal_mutex);
	philo->is_eating = false;
	pthread_mutex_unlock(philo->meal_mutex);
	drop_forks(philo);
	return (true);
}

bool	nap(t_philo *philo)
{
	if (stop(philo->params))
		return (false);
	print(SLEEPING, philo);
	ft_usleep(philo->params->time_to_sleep);
	return (true);
}

bool	think(t_philo *philo)
{
	if (stop(philo->params))
		return (false);
	print(THINKING, philo);
	return (true);
}
