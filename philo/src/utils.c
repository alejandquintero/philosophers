/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:53:26 by aquinter          #+#    #+#             */
/*   Updated: 2024/05/25 23:01:39 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_sleep(size_t ms)
{
	size_t	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < ms)
	{
		if (usleep(500) == -1)
			printf("usleep error!\n");
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		printf("gettimeofday error!\n");
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}