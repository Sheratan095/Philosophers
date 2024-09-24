/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:20:56 by tfalchi           #+#    #+#             */
/*   Updated: 2024/09/24 18:04:35 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_game_over(t_philo *p);

/**
 @brief Set game over in all the philosophers

 @param data Pointer to main structure

 @details
	Being the double liked list a ring, the last is connected with the first
		so, first of all, we have to set game over in first philosopher
	Pass through the list of philosophers untill (current philo != first philo)
		Set game over
*/
void	game_over(t_data *data)
{
	t_philo	*philo;

	philo = data->first_philo;
	set_game_over(philo);
	if (philo->right_philo)
		philo = philo->right_philo;
	while (philo != data->first_philo)
	{
		set_game_over(philo);
		if (philo->right_philo)
			philo = philo->right_philo;
	}
}

/**
 @brief Set the status of game to 0 => game over

 @param philo Pointer to the philosopher

 @details
	Lock the philosopher
	Update the value of game
	Unlock the philosopher
*/
static void	set_game_over(t_philo *p)
{
	pthread_mutex_lock(&p->philo_lock);
	p->game = 0;
	pthread_mutex_unlock(&p->philo_lock);
}
