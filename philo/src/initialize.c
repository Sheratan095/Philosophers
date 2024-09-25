/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:53:56 by maceccar          #+#    #+#             */
/*   Updated: 2024/09/24 17:48:46 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*new_philo(t_data *data, int id, t_philo *left_philo);
static t_bool	distribute_forks(t_data *data);
static t_fork	*new_fork(t_data *data);

/**
 @brief Create the "table" (philosophers and forks)

 @param data Pointer to main structure

 @details
	i starts from 1 beacause philos id must start from 1
	Crete 1° philo with NULL as left_philo beacause is the first one
		so his left philo will be assigned at the end
	Assign it to data->first_philo
	Create all the other philosophers
		The one on the rigth of the current one will be the new one
		Memcheck
		Connect the new one with the current one
		philo_tmp go on to the new one
	Connect the last philosopher with the firt one in data
	Connect the first philosopher with the last one
	Try to distribute the forks
	Print an error and exit in case of error
	
 @note
	It's used the "right creation"

 @retval Pointer to main struct
 @retval NULL if something went wrong with allocation
*/
t_data	*initialize_table(t_data *data)
{
	t_philo	*philo_tmp;
	int		i;

	i = 1;
	philo_tmp = new_philo(data, i++, NULL);
	if (!philo_tmp)
		return (NULL);
	data->first_philo = philo_tmp;
	while (i <= data->number_of_philosophers)
	{
		philo_tmp->right_philo = new_philo(data, i, philo_tmp);
		if (!philo_tmp->right_philo)
			return (NULL);
		philo_tmp->right_philo->left_philo = philo_tmp;
		philo_tmp = philo_tmp->right_philo;
		i++;
	}
	philo_tmp->right_philo = data->first_philo;
	data->first_philo->left_philo = philo_tmp;
	if (!distribute_forks(data))
		return (free_all(data, "Error\n fork allocation failed"));
	return (data);
}

/**
 @brief Create a new philosopher

 @param data Pointer to main structure
 @param id Id of the new philosopher
 @param left_philo Pointer to the previous philosopher

 @details
	Allocate the new philosopher and initialize its mutex
		Memcheck for both
	Assign the id
	if (left_philo) (not the first philo)
		new_philo->left_philo = left_philo
	else (it's the first philo)
		new_philo->left_philo = NULL
	Assign NULL to the right philo of the new one
	The birthday will be the same for all philosophers
	Get all the other fields

 @retval New philosopher if everithing went well
 @retval NULL if something went wrong with allocation
*/
static t_philo	*new_philo(t_data *data, int id, t_philo *left_philo)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo || pthread_mutex_init(&philo->philo_lock, NULL))
		return (free_all(data, "Error\n allocation failed"));
	philo->id = id;
	if (left_philo)
		philo->left_philo = left_philo;
	else
		philo->left_philo = NULL;
	philo->right_philo = NULL;
	philo->birthday = data->timestamp;
	philo->last_meal = get_current_time();
	philo->game = 1;
	philo->meals_eaten = 0;
	philo->data = data;
	return (philo);
}

/**
 @brief Distribute the forks between the philosophers

 @param data Pointer to main structure

 @details
	Pass through the list of philosophers
	Create a new fork
	Assign to the right fork of the current philo the new fork
	Go to the next philosopher
	Assign to the left fork of the current philo the new fork

 @retval true if everithing went well
 @retval false if something went wrong with fork allocation
*/
static t_bool	distribute_forks(t_data *data)
{
	int		i;
	t_philo	*philo;
	t_fork	*fork;

	philo = data->first_philo;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		fork = new_fork(data);
		if (!fork)
			return (false);
		philo->r_fork = fork;
		philo = philo->right_philo;
		philo->l_fork = fork;
		i++;
	}
	return (true);
}

/**
 @brief Create new fork

 @param data Pointer to main structure

 @details
	Allocate the new fork and memcheck
	Inizialize the mutex and check the initialization
	In case of an error in both operation
		Print error and return NULL

 @retval Pointer to the new fork
 @retval NULL if something went wrong
*/
static t_fork	*new_fork(t_data *data)
{
	t_fork	*new_fork;

	new_fork = malloc(sizeof(t_fork));
	if (!new_fork)
		return (free_all(data, "Error\n fork allocation failed"));
	if (pthread_mutex_init(&new_fork->fork, NULL))
		return (free_all(data, "Error\n fork allocation failed"));
	return (new_fork);
}
