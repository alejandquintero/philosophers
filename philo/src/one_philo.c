/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:22:40 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/19 22:23:22 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

bool	handle_one_philo(t_philo *philo)
{
	take_left_fork(philo);
	drop_left_fork(philo);
	ft_usleep(philo->params->time_to_die);
	return (false);
}
