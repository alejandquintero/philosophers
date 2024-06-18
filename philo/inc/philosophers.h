/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:11:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/18 21:16:22 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define REQUIRED_ARGUMENTS 5
# define OPTIONAL_ARGUMENTS 6
# define WRONG_INPUT "Wrong input\n"
# define SYSTEM_ERROR "System error\n"
# define INVALID_PHILO_NBRS "Invalid philosopher numbers\n"
# define INVALID_TIME_DIE "Invalid time to die\n"
# define INVALID_TIME_EAT "Invalid time to eat\n"
# define INVALID_TIME_SLEEP "Invalid time to sleep\n"
# define INVALID_MEALS "Invalid number of times each philosopher must eat\n"
# define NO_MEAL_LIMIT -1
# define ERROR 1
# define SUCCESS 1

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
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
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
	u_int64_t		last_meal_time;
	u_int64_t		start_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*stop_mutex;
	pthread_mutex_t	*log_mutex;
	pthread_mutex_t	*meal_mutex;
	t_params		*params;
}	t_philo;

void	init_philos(t_params *params, t_philo *philos);
void	destroy_and_free(t_params *params, t_philo *philo);
void	print(char *msg, t_philo *philo, char *color);
int		ft_usleep(u_int64_t ms);
long	ft_stol(const char *str);
u_int64_t	get_current_time(void);
bool	init_forks(t_params *params);
bool	init_mutex_flags(t_params *params);
bool	init_threads(t_philo *philos, t_params *p);
bool	init_data(t_params *params, t_philo **philos);
bool	is_digit(char *str);
bool	eat(t_philo *philo);
bool	nap(t_philo *philo);
bool	think(t_philo *philo);
bool	philosopher_dead(t_philo *philos);
bool	all_philosophers_ate(t_philo *philos);
bool	stop(t_params *params);

#endif
