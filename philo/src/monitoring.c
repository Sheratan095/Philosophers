/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:43:14 by maceccar          #+#    #+#             */
/*   Updated: 2024/10/11 15:27:54 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*check_philosophers(t_data *data);
static t_bool	check_philosopher(t_philo *philo);
static t_bool	check_meals(t_data *data);
static t_bool	check_meal(t_philo *philo);

/**
 @brief Monitoring of the state of program

 @param data Pointer to the main struct

 @details
	Wait until no one dies or all of them are satisfied
	Check if they are all satisfied or someone died
	Terminate the program
*/
void	monitor(t_data *data)
{
	while (!check_philosophers(data))
		usleep(2000);
	if (check_meals(data) && data->number_of_philosophers != 1)
		ft_mutex_write(data->first_philo, "each philosopher is satisfied");
	else
		ft_mutex_write(check_philosophers(data), "has died of hunger.");
	game_over(data);
}

/**
 @brief Check all the philosphers

 @param data Pointer to the main struct

 @details
	Check if all the philosophers are still alive or satisfied

 @retval Death Philo
 @retval NULL if nothing happened
*/
static t_philo	*check_philosophers(t_data *data)
{
	t_philo	*philo;

	philo = data->first_philo;
	if (check_philosopher(philo))
		return (philo);
	if (philo->right_philo)
		philo = philo->right_philo;
	while (philo != data->first_philo)
	{
		if (check_philosopher(philo))
			return (philo);
		if (philo->right_philo)
			philo = philo->right_philo;
	}
	return (NULL);
}

/**
 @brief Check the philospher

 @param philo Pointer to the philosopher

 @details
	philo_satisfied is staitc because it's used to keep in memory in memory
		the number of satisfied philosophers
		It's resetted at each new call of monitoring()
			=> when the current philo is the first
		and (just to be sure) at the end of current call
			=> when the current philo is the last
	Lock the philo mutex
	Check if the current philosopher is dead (lifetime must be < time to live)
	Unlock the philo mutex
	if all the philosophers are satisfied
		return true

 @retval true if one of them is dead ore all of them are satisfied
 @retval NULL if nothing happened
*/
static t_bool	check_philosopher(t_philo *philo)
{
	int			philo_lifetime;
	t_bool		is_dead;
	static int	philos_satisfied;

	if (philo->id == 1)
		philos_satisfied = 0;
	pthread_mutex_lock(&philo->philo_lock);
	philo_lifetime = (int)(get_current_time() - philo->last_meal);
	is_dead = philo_lifetime >= philo->data->time_to_die + 3;
	if (philo->data->meals_count != -1)
		if (philo->meals_eaten > philo->data->meals_count)
			philos_satisfied++;
	pthread_mutex_unlock(&philo->philo_lock);
	if (philos_satisfied == philo->data->number_of_philosophers)
		return (true);
	if (philo->id == philo->data->number_of_philosophers)
		philos_satisfied = 0;
	return (is_dead);
}

/**
 @brief Check if the all philosophers are satisfied

 @param data Pointer to the main struct

 @details
	if (number of meals == -1) => not specified
		return false
	Check if each philosopher is satisfied
	if one them is not
		return false
	if all of them are satisfied
		return true

 @return true if philosophers have eaten enough times
 @return false if philosophers haven't eaten enough times
*/
static t_bool	check_meals(t_data *data)
{
	t_philo	*philo;

	if (data->meals_count == -1)
		return (false);
	philo = data->first_philo;
	if (check_meal(philo))
		return (false);
	if (philo->right_philo)
		philo = philo->right_philo;
	while (philo != data->first_philo)
	{
		if (check_meal(philo))
			return (false);
		if (philo->right_philo)
			philo = philo->right_philo;
	}
	return (true);
}

/**
 @brief Check if the philosopher is satisfied

 @param philo Pointer to the philosopher

 @details
	Lock the philosopher mutex
	Check if the number of meals eaten by the philo corresponds
		to the number of meals that should be eaten by each philosopher
	Unlock the philosopher mutex

 @return true if the philosopher ate enough times
 @return false if the philosopher didn't eat enough times
*/
static t_bool	check_meal(t_philo *philo)
{
	int	is_satisfied;

	pthread_mutex_lock(&philo->philo_lock);
	is_satisfied = (philo->meals_eaten == philo->data->meals_count);
	pthread_mutex_unlock(&philo->philo_lock);
	return (is_satisfied);
}
