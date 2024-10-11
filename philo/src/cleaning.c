/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:05:37 by maceccar          #+#    #+#             */
/*   Updated: 2024/10/11 15:18:59 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_philos(t_data *data);
static void	join_threads(t_data *data);

/**
 @brief Free everithing

 @param data Pointer to main structure
 @param error Optional error to print

 @details
	if (error)
		print the optional error
	if (ther's at least one philo)
		join the threads
		free all the philos
	Destroy the mutex in data
	free the main structure	

 @return NULL beacause, in case this function is called in subfunction
		=> the "main function" know the error happened
*/
void	*free_all(t_data *data, char *error)
{
	if (error)
		printf("%s\n", error);
	if (!data)
		return (NULL);
	if (data->first_philo)
	{
		join_threads(data);
		free_philos(data);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->p_mutex);
	if (data)
		free(data);
	return (NULL);
}

/**
 @brief Free all the philosophers

 @param data Pointer to main structure

 @details
	Check it ther's at least one philos
	Keep the cursur with data->first_philo
	For each philosopher
		Keep in memory the cursor (new philo)
		Destroy all the mutex of the current philosopher
		free the right fork
		free current philo
		Resume the cursor and go on
*/
static void	free_philos(t_data *data)
{
	t_philo	*philo_tmp;
	int		i;

	i = 0;
	if (!data->first_philo)
		return ;
	philo_tmp = data->first_philo;
	while (i < data->number_of_philosophers)
	{
		data->first_philo = philo_tmp->right_philo;
		pthread_mutex_destroy(&philo_tmp->r_fork->fork);
		pthread_mutex_destroy(&philo_tmp->philo_lock);
		free(philo_tmp->r_fork);
		free(philo_tmp);
		philo_tmp = data->first_philo;
		i++;
	}
}

/**
 @brief Join all threads to the main one

 @param data Pointer to main structure

 @details
	For each philosopher
		join the corresponding thread wiht its id

*/
static void	join_threads(t_data *data)
{
	int		i;
	t_philo	*philo_tmp;

	philo_tmp = data->first_philo;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(philo_tmp->thread_id, NULL);
		philo_tmp = philo_tmp->right_philo;
		i++;
	}
}
