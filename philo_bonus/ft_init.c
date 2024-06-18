/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:12:58 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/18 21:27:27 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	child_philo(t_philo *philo, int id, t_table *table)
{
	philo->id = id;
	philo->pid = -1;
	philo->end = 0;
	philo->full = 0;
	philo->meals_counter = 0;
	philo->table = table;
}

t_philo	*init(t_table *table, t_free **alloc)
{
	t_philo	*philo;
	int		i;

	philo = ft_malloc(alloc, table->philo_nbr * sizeof(t_philo));
	i = -1;
	while (++i < table->philo_nbr)
		child_philo((philo + i), i + 1, table);
	sem_unlink("forks");
	sem_unlink("end");
	sem_unlink("write");
	sem_unlink("ready");
	sem_unlink("stop");
	sem_unlink("full");
	table->s_stop = sem_open("stop", O_CREAT, 0600, 1);
	table->s_end = sem_open("end", O_CREAT, 0600, 0);
	table->s_write = sem_open("write", O_CREAT, 0600, 1);
	table->s_forks = sem_open("forks", O_CREAT, 0600, table->philo_nbr);
	table->s_ready = sem_open("ready", O_CREAT, 0600, 0);
	table->s_full = sem_open("full", O_CREAT, 0600, 0);
	return (philo);
}
