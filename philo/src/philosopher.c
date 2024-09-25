/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:05:01 by maceccar          #+#    #+#             */
/*   Updated: 2024/09/24 17:28:33 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_sleep(t_philo *philo);
static void	philo_eat(t_philo *philo);

/**
 @brief Routine of the philosopher

 @param args Pointer to void, it contains the current philo

 @details
	Retrieve the current philo casting args
	if (id of philo is even)
		The philo start to sleep
	[it's done beacuse the philo's musn't start to eat all togheter]
	Until the game is over
		The current philo eats
	
 @note NULL
*/
void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2)
		philo_sleep(philo);
	while (get_game(philo))
		philo_eat(philo);
	return (NULL);
}

/**
 @brief Sleeping process of the philosopher

 @param philo Pointer to the philosopher

 @details
	Print the sleeping message
	Sleep for time_to_sleep milliseconds
*/
static void	philo_sleep(t_philo *philo)
{
	ft_mutex_write(philo, "is sleeping.");
	ft_usleep(philo->data->time_to_sleep);
}

/**
 @brief Eating process of the philosopher

 @param philo Pointer to the philosopher

 @details
	if (ther's just one philo)
		return
	if the current philo is the last one
		lock (take) right fork and then the left one
	else
		unlock (take) left fork and then the right one
	[it's done because otherwise the last philo would wait forever]
	print the messages for the forks and for eating
	lock the philo
		Update the last meal time
		Update the number of meal
	unlock the philo
	sleep for the eating time
	unlock both forks
	philo starts sleeping
	Now the philo is thinking
*/
static void	philo_eat(t_philo *philo)
{
	if (philo->data->number_of_philosophers == 1)
		return ;
	if (philo->data->number_of_philosophers == philo->id)
	{
		pthread_mutex_lock(&philo->r_fork->fork);
		pthread_mutex_lock(&philo->l_fork->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork->fork);
		pthread_mutex_lock(&philo->r_fork->fork);
	}
	ft_mutex_write(philo, "took right fork.");
	ft_mutex_write(philo, "took left fork.");
	ft_mutex_write(philo, "is eating.");
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_unlock(&philo->r_fork->fork);
	philo_sleep(philo);
	ft_mutex_write(philo, "is thinking.");
}
