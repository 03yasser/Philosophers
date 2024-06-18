/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:13:42 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/18 21:37:56 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	waiter_utils(int *philo_full, t_table *table)
{
	int		i;
	size_t	last_eat;
	size_t	time;
	t_philo	*philo;

	i = -1;
	philo = *table->philos;
	while (++i < table->philo_nbr)
	{
		time = get_time(table);
		pthread_mutex_lock(&philo->m_philo);
		last_eat = philo->last_eat;
		if (philo->full)
			(*philo_full)++;
		pthread_mutex_unlock(&philo->m_philo);
		if ((time - table->start - last_eat) >= (size_t)(table->t_to_die))
		{
			set_var(&table->m_table, &table->end, 1);
			pthread_mutex_lock(&table->m_write);
			return (printf("%lu %d died\n", time - table->start, philo->id), 1);
		}
		philo = philo->next;
		usleep(100);
	}
	return (0);
}

void	*waiter_routine(void *data)
{
	t_table	*table;
	t_philo	*philo;
	int		i;
	int		philo_full;

	table = (t_table *)data;
	philo = *table->philos;
	while (!get_var(&table->m_table, &table->ready))
		usleep(5000);
	while (1)
	{
		i = 0;
		philo_full = 0;
		if (waiter_utils(&philo_full, table))
			return (NULL);
		if (philo_full == table->philo_nbr)
		{
			set_var(&table->m_table, &table->end, 1);
			pthread_mutex_lock(&table->m_write);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
