/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:53:26 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/10 21:59:30 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print(char *msg, t_philo *philo, char *color)
{
	pthread_mutex_lock(philo->stop_mutex);
	if (!philo->params->stop)
	{
		pthread_mutex_lock(philo->log_mutex);
		printf(
			"%s %zu %d %s\n",
			color,
			get_current_time() - philo->start_time,
			philo->id,
			msg
			);
		pthread_mutex_unlock(philo->log_mutex);
	}
	pthread_mutex_unlock(philo->stop_mutex);
}

int	own_usleep(size_t ms)
{
	size_t	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < ms)
	{
		if (usleep(50) == -1)
			printf("usleep error!\n");
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		printf("gettimeofday error!\n");
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	ft_stol(const char *str)
{
	int		i;
	int		sign;
	long	num;

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
