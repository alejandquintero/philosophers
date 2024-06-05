/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinter <aquinter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:11:46 by aquinter          #+#    #+#             */
/*   Updated: 2024/06/05 21:40:53 by aquinter         ###   ########.fr       */
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
	int				routine_active;
	int				dead_flag;
	int				all_eat;
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	routine_mutex;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	meal_mutex;
}	t_params;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				last_meal_time;
	size_t			start_time;
	int				is_dead; // ?
	int				is_eating;
	int				meals_count;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*routine_mutex; // para el flag de dead_flag
	pthread_mutex_t	*log_mutex; // para printf
	pthread_mutex_t	*meal_mutex; // para cuando este comiendo y necesite consulta el numero de comidas
	t_params		*params;
}	t_philo;

int		own_usleep(size_t ms);
size_t	get_current_time(void);
bool	init_forks(t_params *params);
bool	init_mutex_flags(t_params *params);
void	init_philos(t_params *params, t_philo *philos);
void	destroy_and_free(t_params *params, t_philo *philo);
bool	init_threads(t_philo *philos, t_params *p);
long	ft_stol(const char *str);
bool	init(t_params *params, t_philo **philos);
bool	is_digit(char *str);
void 	print(char *msg, t_philo *philo, char *color);


#endif
