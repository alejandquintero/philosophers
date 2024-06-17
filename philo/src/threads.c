/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:32:39 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/17 23:06:06 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*supervisor_routine(void *p)
{
	t_philo	*philos;

	philos = (t_philo *)p;
	while (true)
	{
		if (a_philosopher_is_dead(p))
			return (NULL);
		if (philos[0].params->number_of_meals != -1)
		{
			if (all_the_philosophers_ate(philos))
				return (NULL);
		}
		ft_usleep(.5);
	}
	return (NULL);
}

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

void	*philo_routine(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 != 0)
		ft_usleep(philo->params->time_to_eat - 10);
	while (loop(philo))
	{
		if (!eat(philo))
			break;
		if (!nap(philo))
			break;
		if (!think(philo))
			break;
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
