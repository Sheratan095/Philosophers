/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:01:24 by lebartol          #+#    #+#             */
/*   Updated: 2024/08/11 14:33:07 by tfalchi          ###   ########.fr       */
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
	t_bool			is_avaible;
}	t_fork;

// Is managed as a "chain" connecting first and last "nodes"
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

void	display_table(t_data *data);

void	*free_all(t_data *data, char *error);

int		create_philo_routine(t_philo *p);

void	ft_mutex_write(t_philo *p, char *str);

void	philo_sleep(t_philo *p);

void	philo_eat(t_philo *p);

t_bool	get_gameover(t_data *data, t_bool ac);

void	monitor(t_data *data);

t_philo	*check_philo(t_data *data);

int		check_death(t_philo *p);

int		check_meal(t_philo *p);

int		get_game(t_philo *p);

void	game_over(t_data *data);

#endif
