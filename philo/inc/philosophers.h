/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:11:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/05/23 23:51:26 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define REQUIRED_ARGUMENTS 5
# define OPTIONAL_ARGUMENTS 6

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_params
{
	int	n_philos;
	int	n_times_to_eat;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}	t_params;

void	print(char *msg);

#endif