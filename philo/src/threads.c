/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:32:39 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/05 21:46:56 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	nap(t_philo *philo)
{
	print("is sleeping", philo, GREEN);
	own_usleep(philo->params->time_to_sleep);
}

void	think(t_philo *philo)
{
	print("is thinking", philo, RED);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print("has taken a fork", philo, CYAN);
	pthread_mutex_lock(philo->r_fork);
	print("has taken a fork", philo, CYAN);
	print("is eating", philo, YELLOW);
	own_usleep(philo->params->time_to_eat);
	philo->last_meal_time = get_current_time();
	philo->meals_count++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

bool is_routine_active(t_philo *philo)
{
	if (philo->params->number_of_meals != -1){
		if (philo->meals_count == philo->params->number_of_meals)
			return (false);
	}
	pthread_mutex_lock(philo->routine_mutex);
	if (!philo->params->routine_active)
	{
		pthread_mutex_unlock(philo->routine_mutex);
		return (false);
	}
	pthread_mutex_unlock(philo->routine_mutex);
	return (true);
}

void	*supervisor_routine(void *p)
{
	t_philo *philos;

	philos = (t_philo *)p;
	
	pthread_mutex_lock(philos[0].log_mutex);
	int	i = 0;
	while (i < philos[0].params->number_of_philos)
	{
		printf("%d\n", philos[i].id);
		printf("%d\n", philos[i].is_dead);
		printf("%d\n", philos[i].is_eating);
		printf("%d\n", philos[i].meals_count);
		printf("%d\n", philos[i].params->time_to_die);
		printf("l %p\n", philos[i].l_fork);
		printf("r %p\n", philos[i].r_fork);
		printf("%p\n", philos[i].routine_mutex);
		printf("%p\n", philos[i].log_mutex);
		printf("%p\n", philos[i].meal_mutex);
		printf("=====================\n");
		i++;
	}
	pthread_mutex_unlock(philos[0].log_mutex);
	return (NULL);
}

void	*philo_routine(void *p)
{
	t_philo *philo;
	philo = (t_philo *)p;
	if (philo->id % 2 != 0)
		own_usleep(1);
	while (is_routine_active(philo))
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