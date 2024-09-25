/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:55:14 by lebartol          #+#    #+#             */
/*   Updated: 2024/09/24 15:38:31 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 @brief Concurrent printing

 @param philo Pointer to the philosopher
 @param str Pointer to the message to print

 @details
	Check the game
	Lock the write mutex
	Print [current time stamp in millisecond, id of philo, message]
	Unlock the write mutex
*/
void	ft_mutex_write(t_philo *philo, char *str)
{
	size_t	life_span;

	if (!get_game(philo))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	life_span = get_current_time() - philo->birthday;
	printf("[%zu]\t%d\t%s\n", life_span, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

/**
 @brief Calculates the current time in milliseconds

 @details
	timeval is a struct that old two fields
		tv_sec: the number of seconds
		tv_usec: the number of microseconds (1/1,000,000 seconds)
	gettimeofday() populate populate the timeval struct
	if it return -1
		print error
	seconds converted in milliseconds (1 sec = 1000ms) +
	microseconds converted in millisecond (1µ = 0.001ms)

 @return The current time in milliseconds
*/
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (write(2, "gettimeofday() error\n", 22), 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 @brief Suspends the execution for a specified number of milliseconds

 @param milliseconds Number of milliseconds that the thread must sleep

 @details
	Retieve the current fime (starting time)
	The loop continues until the difference between the current time 
		and the starting time reaches the requested number of milliseconds
		At each iteration call usleep for 1000µ = 1ms

 @param milliseconds The duration in milliseconds for which 
	the execution should be suspended.

 @return 0 on success. The return value indicates successful 
	completion of the function.
*/
void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(1000);
}

/**
 @brief Get the game status

 @param philo Pointer to the philosopher

 @details
	Lock the philo mutex
	Save the the same status to return afterr unlock of philo mutex
	Unlock the philo mutex

 @return Game status
*/
int	get_game(t_philo *p)
{
	int	i;

	pthread_mutex_lock(&p->philo_lock);
	i = p->game;
	pthread_mutex_unlock(&p->philo_lock);
	return (i);
}
