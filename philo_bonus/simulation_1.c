/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:13:42 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/16 12:08:57 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	waiter_utils(int *philo_full, t_table *table)
// {
// 	int		i;
// 	size_t	last_eat;
// 	size_t	time;
// 	t_philo	*philo;
// 	(void)philo_full;
// 	i = -1;
// 	philo = table->philo;
// 	time = get_time(table);
// 	sem_wait(philo->s_philo);
// 	last_eat = philo->last_eat;
// 	// if (philo->full)
// 	// 	(*philo_full)++;
// 	sem_post(philo->s_philo);
// 	if ((time - table->start - last_eat) >= (size_t)(table->t_to_die))
// 	{
// 		sem_wait(philo->s_philo);
// 		philo->end = 1;
// 		sem_post(philo->s_philo);
// 		sem_wait(table->s_write);
// 		printf("%lu %d died\n", time - table->start, philo->id);
// 		return (1);
// 	}
// 	return (0);
// }

// void	*waiter_routine(void *data)
// {
// 	t_table	*table;
// 	t_philo	*philo;
// 	int		i;
// 	int		philo_full;

// 	philo = (t_philo *)data;
// 	table = philo->table;
// 	while (1)
// 	{
// 		i = 0;
// 		philo_full = 0;
// 		if (waiter_utils(&philo_full, table))
// 			return (NULL);
// 		// if (philo_full == table->philo_nbr)
// 		// {
// 		// 	set_var(&table->m_table, &table->end, 1);
// 		// 	pthread_mutex_lock(&table->m_write);
// 		// 	return (NULL);
// 		// }
// 		usleep(1000);
// 	}
// 	return (NULL);
// }
