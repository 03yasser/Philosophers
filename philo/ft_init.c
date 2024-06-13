/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:12:58 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/13 10:26:33 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**create_philos(t_free **alloc, t_table *table)
{
	int			i;
	t_philo		**philos;
	t_philo		*philo;

	philos = ft_malloc(alloc, sizeof(t_philo **));
	*philos = NULL;
	i = 0;
	while (i < table->philo_nbr)
	{
		philo = ft_malloc(alloc, sizeof(t_philo));
		philo->full = 0;
		philo->fork_locked = 0;
		philo->last_eat = 0;
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->table = table;
		pthread_mutex_init(&philo->m_fork, NULL);
		pthread_mutex_init(&philo->m_philo, NULL);
		philo->next = NULL;
		ft_lstadd_back(philos, philo);
		i++;
	}
	philo->next = *philos;
	return (philos);
}

void	data_init(t_table *table, t_free **alloc)
{
	table->end = 0;
	table->ready = 0;
	table->threads_runing = 0;
	table->alloc = alloc;
	table->philos = create_philos(alloc, table);
	pthread_mutex_init(&table->m_table, NULL);
	pthread_mutex_init(&table->m_write, NULL);
}
