/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:38:17 by maceccar          #+#    #+#             */
/*   Updated: 2024/09/25 17:31:39 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c);

t_bool	ft_is_string_numeric(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			if (i == 0)
			{
				if (str[i] != '-' && str[i] != '+')
					return (false);
			}
			else
				return (false);
		}
		i++;
	}
	return (true);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	res = 0;
	while (ft_isdigit(str[i]))
		res = res * 10 + (str[i++] - '0');
	return (res * sign);
}

long	ft_atol(const char *s)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*s == ' ' || (*s > 8 && *s < 14))
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	while (ft_isdigit(*s))
		res = res * 10 + *s++ - '0';
	return (res * sign);
}

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}
