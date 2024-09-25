/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:55:57 by maceccar          #+#    #+#             */
/*   Updated: 2024/09/25 17:34:11 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"

typedef enum e_bool
{
	false,
	true
}	t_bool;

int		ft_atoi(const char *str);

long	ft_atol(const char *s);

t_bool	ft_is_string_numeric(const char *str);

void	ft_usleep(size_t milliseconds);

size_t	get_current_time(void);

#endif
