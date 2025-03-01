/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:24:04 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/18 21:25:58 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(t_table *table)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		error2("gettimeofday failure", table);
		return (0);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds, t_table *table)
{
	size_t	start;

	start = get_time(table);
	while ((get_time(table) - start) < milliseconds)
		usleep(500);
	return (0);
}

int	check_input(t_table table)
{
	if (table.philo_nbr < 1 || table.philo_nbr > 200)
		return (1);
	if (table.t_to_die == 0)
		return (1);
	if (table.t_to_eat == 0)
		return (1);
	if (table.t_to_sleep == 0)
		return (1);
	if (table.limit_meals == 0)
		return (1);
	return (0);
}
