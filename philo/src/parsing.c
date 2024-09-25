/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:05:01 by maceccar          #+#    #+#             */
/*   Updated: 2024/09/25 17:29:00 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_data	*load_arguments(t_data *data, char *argv[], int argc);
static int		get_single_arg(int *taget, char *arg);

/**
 @brief Intialize data and parse the parameters from argv

 @param argv Matrix with arguments
 @param argc Number of arguments

 @details
	Check argc, if it's wrong => print an error
	Allocate data and memcheck
	Initialize all mutex and check their initialization
	Initialize the fields of the main struct
	Load the arguments
	if (data exist) => everithing went well
		Get current time

 @retval main struct
 @retval NULL if something went wrong
*/
t_data	*parse_arguments(int argc, char *argv[])
{
	t_data	*data;

	data = NULL;
	if (argc != 5 && argc != 6)
		return (free_all(data, "Error\n wrong number of arguments\n"));
	data = malloc(sizeof(t_data));
	if (!data)
		return (free_all(data, "Error\n allocation failed\n"));
	if (pthread_mutex_init(&data->write_lock, NULL) != 0
		|| pthread_mutex_init(&data->game_lock, NULL) != 0
		|| pthread_mutex_init(&data->p_mutex, NULL) != 0)
		return (free_all(data, "Error\n writing lock allocation failed\n"));
	data->first_philo = NULL;
	data->game_over = false;
	data = load_arguments(data, argv, argc);
	if (data)
		data->timestamp = get_current_time();
	return (data);
}

/**
 @brief Load all the parameters from argv

 @param data Pointer to main structure
 @param argv Matrix with arguments
 @param argc Number of arguments

 @details
	Try to get all the mandatory parameters from argv with get_single_arg
	Check the result, if something went wrong (-1)
		free all the program
		print an error depending on which parameter isn't correct
	if count == 6
		Try to get the number of meals (optional) and check
	else
		meals_count (in the main struct) will be 1

 @retval main struct
 @retval NULL if one of the parameters is invalid
*/
static t_data	*load_arguments(t_data *data, char *argv[], int argc)
{
	if (get_single_arg(&data->number_of_philosophers, argv[1]) == -1)
		return (free_all(data, "Error\n number of philosophers not valid\n"));
	if (get_single_arg(&data->time_to_die, argv[2]) == -1)
		return (free_all(data, "Error\n time to die not valid\n"));
	if (get_single_arg(&data->time_to_eat, argv[3]) == -1)
		return (free_all(data, "Error\n time to eat not valid\n"));
	if (get_single_arg(&data->time_to_sleep, argv[4]) == -1)
		return (free_all(data, "Error\n time to live not valid\n"));
	if (argc == 6)
	{
		if (get_single_arg(&data->meals_count, argv[5]) == -1)
			return (free_all(data, "Error\n number of eating not valid\n"));
	}
	else
		data->meals_count = -1;
	return (data);
}

/**
 @brief Check the single arg and assign it to the target pointer

 @param target Pointer to the respective value in the main struct
 @param arg Pointer to the string that contains the arg

 @details
	Check if string is numeric
		(it includes first sign: ++1: wrong, +1: ok)
	Check with atol if the number respects the limits of integer
	Assign the value to target pointer with atoi() and check the conversion

 @retval target
 @retval -1 if the value ins't valid
*/
static int	get_single_arg(int *taget, char *arg)
{
	if (!ft_is_string_numeric(arg))
		return (-1);
	if (ft_atol(arg) < INT_MIN || ft_atol(arg) > INT_MAX)
		return (-1);
	*taget = ft_atoi(arg);
	if (*taget <= 0)
		return (-1);
	return (*taget);
}
