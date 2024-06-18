/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:50:59 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/18 20:54:20 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	drop_left_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
}

void	drop_right_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
}

bool	take_left_fork(t_philo *philo)
{
	if (stop(philo->params))
		return (false);
	pthread_mutex_lock(philo->left_fork);
	print("has taken a fork", philo, GREEN);
	return (true);
}

bool	take_right_fork(t_philo *philo)
{
	if (stop(philo->params))
		return (false);
	pthread_mutex_lock(philo->right_fork);
	print("has taken a fork", philo, GREEN);
	return (true);
}

bool	take_forks(t_philo *philo)
{
	if (!take_left_fork(philo))
		return (false);
	if (philo->params->number_of_philos == 1)
	{
		drop_left_fork(philo);
		ft_usleep(philo->params->time_to_die);
		return (false);
	}
	if (!take_right_fork(philo))
	{
		drop_left_fork(philo);
		return (false);
	}
	return (true);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

bool	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (false);
	print("is eating", philo, YELLOW);
	pthread_mutex_lock(philo->meal_mutex);
	philo->is_eating = 1;
	philo->last_meal_time = get_current_time();
	philo->meals_count++;
	pthread_mutex_unlock(philo->meal_mutex);
	ft_usleep(philo->params->time_to_eat);
	pthread_mutex_lock(philo->meal_mutex);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->meal_mutex);
	drop_left_fork(philo);
	drop_right_fork(philo);
	return (true);
}

bool	nap(t_philo *philo)
{
	if (stop(philo->params))
		return (false);
	print("is sleeping", philo, CYAN);
	ft_usleep(philo->params->time_to_sleep);
	return (true);
}

bool	think(t_philo *philo)
{
	if (stop(philo->params))
		return (false);
	print("is thinking", philo, MAGENTA);
	return (true);
}
