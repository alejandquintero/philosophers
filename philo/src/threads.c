/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:32:39 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/19 22:59:45 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*supervisor_routine(void *p)
{
	t_philo	*philos;
	int		number_of_meals;

	philos = (t_philo *)p;
	number_of_meals = philos[0].params->number_of_meals;
	while (true)
	{
		if (philosopher_dead(p))
			return (NULL);
		if (number_of_meals != NO_MEAL_LIMIT)
		{
			if (all_philosophers_ate(philos))
				return (NULL);
		}
		ft_usleep(.5);
	}
	return (NULL);
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
			return (NULL);
		if (!nap(philo))
			return (NULL);
		if (!think(philo))
			return (NULL);
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
