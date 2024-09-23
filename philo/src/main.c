/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:45:02 by lebartol          #+#    #+#             */
/*   Updated: 2024/08/11 16:01:23 by tfalchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_data *data);

int	get_game(t_philo *p)
{
	int	i;

	pthread_mutex_lock(&p->philo_lock);
	i = p->game;
	pthread_mutex_unlock(&p->philo_lock);
	return (i);
}

// TODO spostare questa cosa direttamente in initialize_table()
static int	create_threads(t_data *data)
{
	t_philo	*p;

	p = data->first_philo;
	if ((pthread_create(&p->thread_id, NULL, philo_routine, p)))
		return (1);
	p = p->right_philo;
	while (p != data->first_philo)
	{
		if (pthread_create(&p->thread_id, NULL, philo_routine, p))
			return (1);
		p = p->right_philo;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = parse_arguments(argc, argv);
	if (!data)
		return (1);
	data = initialize_table(data);
	if (!data)
		return (1);
	if (!create_threads(data))
		monitor(data);
	monitor(data);
	free_all(data, NULL);
}
