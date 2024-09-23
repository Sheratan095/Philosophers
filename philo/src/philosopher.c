/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:05:01 by lebartol          #+#    #+#             */
/*   Updated: 2024/08/11 14:24:05 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		philo_sleep(t_philo *p);
static void		philo_eat(t_philo *p);

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2)
		philo_sleep(philo);
	while (get_game(philo))
	{
		philo_eat(philo);
	}
	return (NULL);
}

static void	philo_sleep(t_philo *p)
{
	ft_mutex_write(p, "is sleeping.");
	ft_usleep(p->data->time_to_sleep);
}

static void	philo_eat(t_philo *p)
{
	if (p->data->number_of_philosophers == 1)
		return ;
	if (p->data->number_of_philosophers == p->id)
	{
		pthread_mutex_lock(&p->r_fork->fork);
		pthread_mutex_lock(&p->l_fork->fork);
	}
	else
	{
		pthread_mutex_lock(&p->l_fork->fork);
		pthread_mutex_lock(&p->r_fork->fork);
	}
	ft_mutex_write(p, "took right fork.");
	ft_mutex_write(p, "took left fork.");
	ft_mutex_write(p, "is eating.");
	pthread_mutex_lock(&p->philo_lock);
	p->last_meal = get_current_time();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->philo_lock);
	ft_usleep(p->data->time_to_eat);
	pthread_mutex_unlock(&p->l_fork->fork);
	pthread_mutex_unlock(&p->r_fork->fork);
	philo_sleep(p);
	ft_mutex_write(p, "is thinking.");
}
