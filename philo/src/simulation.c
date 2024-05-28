/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 20:32:39 by aquinter          #+#    #+#             */
/*   Updated: 2024/05/28 21:56:48 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*s_routine(void *p)
{
	(void)p;
	return (NULL);
}

void	*p_routine(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	if (philo->params->number_of_meals != -1)
	{
		while (no_dead() && no_all_eated())
		{
			eat()
			sleep();
			think();
		}
	}
	else
	{
		while (!no_dead())
		{
			eat()
			sleep();
			think();
		}
		
	}
	return (NULL);
}

bool	init_simulation(t_philo *philos, t_params *p, t_supervisor *s)
{
	int			i;

	if (pthread_create(&s->thread, NULL, &s_routine, (void *)philos) != 0)
		return (destroy_and_free(p, philos), false);
	i = 0;
	while (i < p->number_of_philos)
	{ 
		if (pthread_create(&philos[i].thread, NULL, &p_routine, 
				(void *)&philos[i]) != 0)
			return (destroy_and_free(p, philos), false);
		i++;
	}
	i = 0;
	if (pthread_join(s->thread, NULL))
			return (destroy_and_free(p, philos), false);
	while (i < p->number_of_philos)
	{ 
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (destroy_and_free(p, philos), false);
		i++;
	}
	return (true);	
}