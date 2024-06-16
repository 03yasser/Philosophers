/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:12:58 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/16 14:09:36 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(t_free **alloc)
{
	t_philo		*philo;


	philo = ft_malloc(alloc, sizeof(t_philo));
	philo->end = 0;
	philo->full = 0;
	philo->last_eat = 0;
	philo->meals_counter = 0;
	philo->next = NULL;
	philo->id = 0;
	return (philo);
}

void	data_init(t_table *table, t_free **alloc)
{
	sem_unlink("end");
	sem_unlink("table");
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("ready");
	table->alloc = alloc;
	table->philo = create_philo(alloc);
	// table->philo->table = ft_malloc(alloc, sizeof(t_table*));
	table->philo->table = table;
	table->s_end = sem_open("end", O_CREAT, 0600, 0);
	table->s_ready = sem_open("ready", O_CREAT, 0600, 0);
	table->s_table = sem_open("table", O_CREAT, 0600, 1);
	table->s_forks = sem_open("forks", O_CREAT, 0600, table->philo_nbr);
	if (table->s_forks == SEM_FAILED)
		perror("sem_open");
	table->s_write = sem_open("write", O_CREAT, 0600, 1);
}
