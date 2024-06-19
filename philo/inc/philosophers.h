/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:11:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/19 22:57:43 by aquinter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>
# include "constants.h"

typedef struct s_params
{
	bool			stop;
	int				number_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
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
	bool			is_eating;
	int				meals_count;
	long			last_meal_time;
	long			start_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*stop_mutex;
	pthread_mutex_t	*log_mutex;
	pthread_mutex_t	*meal_mutex;
	t_params		*params;
}	t_philo;

long long	ft_stol(const char *str);
long		get_time(void);
bool		init_mutex_flags(t_params *params);
bool		init_threads(t_philo *philos, t_params *p);
bool		init_data(t_params *params, t_philo **philos);
bool		is_digit(char *str);
bool		eat(t_philo *philo);
bool		nap(t_philo *philo);
bool		think(t_philo *philo);
bool		philosopher_dead(t_philo *philos);
bool		all_philosophers_ate(t_philo *philos);
bool		stop(t_params *params);
bool		check_input(int argc, char *argv[], t_params *params);
bool		handle_one_philo(t_philo *philo);
bool		take_left_fork(t_philo *philo);
bool		take_right_fork(t_philo *philo);
bool		take_forks(t_philo *philo);
bool		loop(t_philo *philo);
bool		init_forks(t_params *params);
void		drop_left_fork(t_philo *philo);
void		init_philos(t_params *params, t_philo *philos);
void		destroy_and_free(t_params *params, t_philo *philo);
void		print(char *msg, t_philo *philo);
void		ft_usleep(long ms);
void		drop_right_fork(t_philo *philo);
void		drop_forks(t_philo *philo);

#endif
