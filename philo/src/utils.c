/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:53:26 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/19 23:00:46 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print(char *msg, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(philo->log_mutex);
	time = get_time() - philo->start_time;
	if (!stop(philo->params))
	{
		printf("%09lu %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(philo->log_mutex);
}

void	ft_usleep(long ms)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < ms)
	{
		if (usleep(50) == -1)
			printf(SYSTEM_ERROR);
	}
}

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		printf(SYSTEM_ERROR);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	ft_stol(const char *str)
{
	int			i;
	int			sign;
	long long	num;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	return (num * sign);
}

bool	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 58)
			return (false);
		i++;
	}
	return (true);
}
