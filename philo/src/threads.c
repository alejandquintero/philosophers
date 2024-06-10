/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:32:39 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/10 17:48:18 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	check_dead_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_mutex);
	if ((get_current_time() - philo->last_meal_time) > philo->params->time_to_die && !philo->is_eating)
	{
			pthread_mutex_unlock(philo->meal_mutex);
			print("died", philo, RED);
			pthread_mutex_lock(philo->stop_mutex);
			philo->params->stop = true;
			pthread_mutex_unlock(philo->stop_mutex);
			return (true);
	}
	pthread_mutex_unlock(philo->meal_mutex);
	return (false);
}

bool check_meals(t_philo *philo)
{
	if (philo->params->number_of_meals != -1)
	{
		pthread_mutex_lock(philo->meal_mutex);
		if (philo->meals_count >= philo->params->number_of_meals)
		{
			pthread_mutex_unlock(philo->meal_mutex);
			return (true);
		}
		pthread_mutex_unlock(philo->meal_mutex);
	}
	return (false);
}

bool monitor(t_philo *philos)
{
	int	i;
	int	meals_complete;

	i = 0;
	meals_complete = 0;
	while (i < philos[0].params->number_of_philos)
	{
		if (check_dead_philo(&philos[i]))
			return (false);	
		if (check_meals(&philos[i]))
			meals_complete++;
		i++;
	}
	if (meals_complete == philos[0].params->number_of_philos)
	{
		pthread_mutex_lock(philos[0].stop_mutex);
		philos[0].params->stop = true;
		pthread_mutex_unlock(philos[0].stop_mutex);
		return (false);
	}
	return (true);
}

void	nap(t_philo *philo)
{
	print("is sleeping", philo, CYAN);
	own_usleep(philo->params->time_to_sleep);
}

void	think(t_philo *philo)
{
	print("is thinking", philo, WHITE);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print("has taken a fork", philo, GREEN);
	if (philo->params->number_of_philos == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		own_usleep(philo->params->time_to_die);
		return;
	}
	pthread_mutex_lock(philo->r_fork);
	print("has taken a fork", philo, GREEN);
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
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

bool loop(t_philo *philo)
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

void	*supervisor_routine(void *p)
{
	t_philo *philos;

	philos = (t_philo *)p;
	while (1)
	{
		if (!monitor(philos))
			return (NULL);
	}
	return (NULL);
}

void	*philo_routine(void *p)
{
	t_philo *philo;
	philo = (t_philo *)p;
	if (philo->id % 2 != 0)
		own_usleep(10);
	while (loop(philo))
	{
		eat(philo);
		nap(philo);
		think(philo);
	}
	return (NULL);
}

bool	init_threads(t_philo *philos, t_params *p)
{
	int			i;
	pthread_t	supervisor;

	if (pthread_create(&supervisor, NULL, &supervisor_routine, 
			(void *)philos) != 0)
		return (destroy_and_free(p, philos), false);
	i = 0;
	while (i < p->number_of_philos)
	{ 
		if (pthread_create(&philos[i].thread, NULL, &philo_routine, 
				(void *)&philos[i]) != 0)
			return (destroy_and_free(p, philos), false);
		i++;
	}
	i = 0;
	if (pthread_join(supervisor, NULL))
			return (destroy_and_free(p, philos), false);
	while (i < p->number_of_philos)
	{ 
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (destroy_and_free(p, philos), false);
		i++;
	}
	return (true);	
}