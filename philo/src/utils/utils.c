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

void	ft_mutex_write(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->data->write_lock);
	if (!get_game(p))
	{
		pthread_mutex_unlock(&p->data->write_lock);
		return ;
	}
	printf("[%zu]\t%d\t%s\n", (get_current_time() - p->birthday), p->id, str);
	pthread_mutex_unlock(&p->data->write_lock);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(1000);
	return (0);
}

int	get_game(t_philo *p)
{
	int	i;

	pthread_mutex_lock(&p->philo_lock);
	i = p->game;
	pthread_mutex_unlock(&p->philo_lock);
	return (i);
}
