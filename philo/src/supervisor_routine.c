/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:52:15 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/18 21:24:02 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	stop(t_params *params)
{
	bool	stop;

	stop = false;
	pthread_mutex_lock(&params->stop_mutex);
	stop = params->stop;
	pthread_mutex_unlock(&params->stop_mutex);
	return (stop);
}

bool	check_meals(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_mutex);
	if (philo->meals_count >= philo->params->number_of_meals)
	{
		pthread_mutex_unlock(philo->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(philo->meal_mutex);
	return (false);
}

bool	all_philosophers_ate(t_philo *philos)
{
	int	i;
	int	meals_complete;

	i = 0;
	meals_complete = 0;
	while (i < philos[0].params->number_of_philos)
	{
		if (check_meals(&philos[i]))
			meals_complete++;
		i++;
	}
	if (meals_complete == philos[0].params->number_of_philos)
	{
		pthread_mutex_lock(philos[0].stop_mutex);
		philos[0].params->stop = true;
		pthread_mutex_unlock(philos[0].stop_mutex);
		return (true);
	}
	return (false);
}

bool	check_dead_philo(t_philo *philo)
{
	size_t	time_since_last_meal;
	bool	is_dead;

	is_dead = false;
	pthread_mutex_lock(philo->meal_mutex);
	time_since_last_meal = get_current_time() - philo->last_meal_time;
	if (time_since_last_meal > philo->params->time_to_die && !philo->is_eating)
		is_dead = true;
	pthread_mutex_unlock(philo->meal_mutex);
	if (is_dead)
	{	
		
		pthread_mutex_lock(philo->stop_mutex);
		philo->params->stop = true;
		pthread_mutex_unlock(philo->stop_mutex);

		pthread_mutex_lock(philo->log_mutex);		
		printf("%s %09lu %d died\n", RED, get_current_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->log_mutex);

		return (true);
	}
	return (false);
}

bool	philosopher_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].params->number_of_philos)
	{
		if (check_dead_philo(&philos[i]))
			return (true);
		i++;
	}
	return (false);
}
