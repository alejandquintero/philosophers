/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:11:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/17 22:39:34 by aquinter         ###   ########.fr       */
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
# define MAGENTA "\e[0;95m"
# define WHITE ""

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_params
{
	int				stop;
	int				number_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				number_of_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	meal_mutex;
}	t_params;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				is_eating;
	int				meals_count;
	size_t			last_meal_time;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*stop_mutex;
	pthread_mutex_t	*log_mutex;
	pthread_mutex_t	*meal_mutex;
	t_params		*params;
}	t_philo;

void	init_philos(t_params *params, t_philo *philos);
void	destroy_and_free(t_params *params, t_philo *philo);
void	print(char *msg, t_philo *philo, char *color);
int		ft_usleep(size_t ms);
long	ft_stol(const char *str);
size_t	get_current_time(void);
bool	init_forks(t_params *params);
bool	init_mutex_flags(t_params *params);
bool	init_threads(t_philo *philos, t_params *p);
bool	init(t_params *params, t_philo **philos);
bool	is_digit(char *str);
bool	eat(t_philo *philo);
bool	nap(t_philo *philo);
bool	think(t_philo *philo);
bool	a_philosopher_is_dead(t_philo *philos);
bool	all_the_philosophers_ate(t_philo *philos);
bool	stop(t_params *params);

#endif
