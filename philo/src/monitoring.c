/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:43:14 by lebartol          #+#    #+#             */
/*   Updated: 2024/09/25 16:36:13 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*check_philo(t_data *data);
static t_bool	check_death(t_philo *philo);
static t_bool	check_meals(t_data *data);
static t_bool	check_meal(t_philo *philo);

void	monitor(t_data *data)
{
	while (!check_philo(data))
	{
		usleep(2000);
	}
	if (check_meals(data))
		ft_mutex_write(data->first_philo, "each philosopher is satisfied");
	else
		ft_mutex_write(check_philo(data), "has died of hunger.");
	game_over(data);
}

static t_philo	*check_philo(t_data *data)
{
	t_philo	*philo;

	philo = data->first_philo;
	if (check_death(philo))
		return (philo);
	if (philo->right_philo)
		philo = philo->right_philo;
	while (philo != data->first_philo)
	{
		if (check_death(philo))
			return (philo);
		if (philo->right_philo)
			philo = philo->right_philo;
	}
	return (NULL);
}

static t_bool	check_death(t_philo *philo)
{
	t_bool		is_dead;
	static int	y;

	if (philo->id == 1)
		y = 0;
	pthread_mutex_lock(&philo->philo_lock);
	is_dead = ((int)(get_current_time() - philo->last_meal) >= philo->data->time_to_die + 5);
	y += (philo->meals_eaten > philo->data->meals_count && philo->data->meals_count != -1);
	pthread_mutex_unlock(&philo->philo_lock);
	if (y == philo->data->number_of_philosophers)
		return (1);
	if (philo->id == philo->data->number_of_philosophers)
		y = 0;
	return (is_dead);
}

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

static t_bool	check_meal(t_philo *philo)
{
	int	is_satisfied;

	pthread_mutex_lock(&philo->philo_lock);
	is_satisfied = (philo->meals_eaten < philo->data->meals_count);
	pthread_mutex_unlock(&philo->philo_lock);
	return (is_satisfied);
}
