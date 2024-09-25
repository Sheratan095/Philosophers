/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:45:02 by maceccar          #+#    #+#             */
/*   Updated: 2024/09/24 14:42:58 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	create_threads(t_data *data);

/**
 @details
	Parse the arguments and check (it allocates data)
	Initialize the table and check
	Create threads, if everithing is ok => start monitoring
	free all
*/
int	main(int argc, char *argv[])
{
	t_data	*data;

	data = parse_arguments(argc, argv);
	if (!data)
		return (1);
	data = initialize_table(data);
	if (!data)
		return (1);
	if (create_threads(data))
		monitor(data);
	free_all(data, NULL);
}

/**
 @brief Create the threads

 @param data Pointer to main structure

 @details
	Being the double liked list a ring, the last is connected with the first
		so, first of all, we have to create the thread for the first philo
	Then we can crete all the other threads and check the creation

 @retval true if everithing went well
 @retval false if something went wrong during thread creation
*/
static t_bool	create_threads(t_data *data)
{
	t_philo	*p;

	p = data->first_philo;
	if ((pthread_create(&p->thread_id, NULL, philo_routine, p)))
		return (1);
	p = p->right_philo;
	while (p != data->first_philo)
	{
		if (pthread_create(&p->thread_id, NULL, philo_routine, p))
			return (false);
		p = p->right_philo;
	}
	return (true);
}
