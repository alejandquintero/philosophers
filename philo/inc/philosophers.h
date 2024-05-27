/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:11:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/05/25 23:13:10 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define REQUIRED_ARGUMENTS 5
# define OPTIONAL_ARGUMENTS 6
# define RED "\e[0;91m"
# define GREEN "\e[0;92m"
# define YELLOW "\e[0;93m"
# define CYAN "\e[0;96m"

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>


typedef struct s_params
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_meals;
}	t_params;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				last_meal_time;
	int				start_time;
	int				is_dead;
	int				is_eating;
	int				meals_count;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*log_mutex;
	pthread_mutex_t	*meal_mutex;
	t_params		*t_params;
}	t_philo;

typedef struct s_program
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	meal_mutex;
}	t_program;

void	print(char *msg);
int		ft_sleep(size_t ms);
size_t	get_current_time(void);

#endif
