/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:50:59 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/10 22:04:57 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print("has taken a fork", philo, GREEN);
	if (philo->params->number_of_philos == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		own_usleep(philo->params->time_to_die);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print("has taken a fork", philo, GREEN);
	// Todo mejorar
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	print("is eating", philo, YELLOW);
	pthread_mutex_lock(philo->meal_mutex);
	philo->is_eating = 1;
	philo->last_meal_time = get_current_time();
	philo->meals_count++;
	pthread_mutex_unlock(philo->meal_mutex);
	own_usleep(philo->params->time_to_eat);
	pthread_mutex_lock(philo->meal_mutex);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->meal_mutex);
	drop_forks(philo);
}

void	nap(t_philo *philo)
{
	print("is sleeping", philo, CYAN);
	own_usleep(philo->params->time_to_sleep);
}

void	think(t_philo *philo)
{
	print("is thinking", philo, MAGENTA);
}
