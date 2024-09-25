/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:01:24 by maceccar          #+#    #+#             */
/*   Updated: 2024/09/25 17:34:43 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include "utils.h"

typedef struct s_fork
{
	pthread_mutex_t	fork;
}	t_fork;
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				game;
	size_t			last_meal;
	size_t			birthday;

	struct s_philo	*right_philo;
	struct s_philo	*left_philo;

	struct s_data	*data;

	pthread_t		thread_id;
	t_fork			*r_fork;
	t_fork			*l_fork;
	pthread_mutex_t	philo_lock;

}	t_philo;

typedef struct s_data
{
	int				number_of_philosophers;	
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_count;

	t_bool			game_over;
	size_t			timestamp;
	t_philo			*first_philo;

	pthread_mutex_t	write_lock;
	pthread_mutex_t	game_lock;
	pthread_mutex_t	p_mutex;

}	t_data;

t_data	*parse_arguments(int argc, char *argv[]);

t_data	*initialize_table(t_data *data);

void	*philo_routine(void *args);

void	monitor(t_data *data);

void	game_over(t_data *data);

void	*free_all(t_data *data, char *error);

void	ft_mutex_write(t_philo *philo, char *str);

int		get_game(t_philo *philo);

void	display_table(t_data *data);

#endif
