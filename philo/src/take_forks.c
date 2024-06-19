/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:25:10 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/19 23:02:25 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	take_left_fork(t_philo *philo)
{
	if (stop(philo->params))
		return (false);
	pthread_mutex_lock(philo->left_fork);
	print(TAKEN_FORK, philo);
	return (true);
}

bool	take_right_fork(t_philo *philo)
{
	if (stop(philo->params))
		return (false);
	pthread_mutex_lock(philo->right_fork);
	print(TAKEN_FORK, philo);
	return (true);
}

bool	take_forks(t_philo *philo)
{
	if (philo->params->number_of_philos == 1)
		return (handle_one_philo(philo));
	if (philo->id % 2 != 0)
	{
		if (!take_left_fork(philo))
			return (false);
		if (!take_right_fork(philo))
		{
			drop_left_fork(philo);
			return (false);
		}
	}
	else
	{
		if (!take_right_fork(philo))
			return (false);
		if (!take_left_fork(philo))
		{
			drop_right_fork(philo);
			return (false);
		}
	}
	return (true);
}
