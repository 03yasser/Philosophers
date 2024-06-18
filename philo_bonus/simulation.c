/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:02:44 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/18 21:23:57 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*waiter_routine(void *data)
{
	t_philo	*philo;
	t_table	*table;
	size_t	time;
	int		i;

	philo = (t_philo *)data;
	table = philo->table;
	while (1)
	{
		i = 0;
		sem_wait(table->s_stop);
		time = get_time(philo->table) - table->start;
		if (time - philo->last_eat >= (size_t)table->t_to_die)
		{
			sem_wait(philo->table->s_write);
			time = get_time(philo->table) - table->start;
			printf("%lu %d %s\n", time, philo->id, "died");
			sem_post(table->s_end);
			return (NULL);
		}
		sem_post(philo->table->s_stop);
		usleep(1000);
	}
	return (NULL);
}

static void	eat(t_table *table, t_philo *philo)
{
	philo->last_eat = get_time(table) - table->start;
	sem_wait(table->s_forks);
	write_status("has taken a fork", philo, table);
	sem_wait(table->s_forks);
	write_status("has taken a fork", philo, table);
	philo->meals_counter++;
	philo->last_eat = get_time(table) - table->start;
	write_status("is eating", philo, table);
	ft_usleep(table->t_to_eat, table);
	sem_post(table->s_forks);
	sem_post(table->s_forks);
	if (table->limit_meals != -1
		&& philo->meals_counter == table->limit_meals)
		sem_post(table->s_full);
}

static void	philo_routine(t_philo *philo, t_table *table)
{
	sem_wait(table->s_ready);
	if (philo->id % 2 == 0)
		usleep(100);
	philo->last_eat = get_time(table) - table->start;
	pthread_create(&philo->philo, NULL, waiter_routine, philo);
	pthread_detach(philo->philo);
	while (!philo->full)
	{
		write_status("is thinking", philo, table);
		eat(table, philo);
		write_status("is sleeping", philo, table);
		ft_usleep(table->t_to_sleep, table);
	}
	exit(0);
}

void	*t_table_routine(void *data)
{
	t_table	*table;
	int		i;

	i = -1;
	table = (t_table *)data;
	while (++i < table->philo_nbr)
		sem_wait(table->s_full);
	sem_post(table->s_end);
	return (NULL);
}

void	start_simulation(t_table *table, t_philo **philo)
{
	int		i;

	pthread_create(&table->t_table, NULL, t_table_routine, table);
	pthread_detach(table->t_table);
	i = -1;
	table->start = get_time(table);
	while (++i < table->philo_nbr)
	{
		(*philo)[i].pid = fork();
		if ((*philo)[i].pid == -1)
			error2("fork_failed\n", table);
		if ((*philo)[i].pid == 0)
			philo_routine(&(*philo)[i], table);
	}
	i = -1;
	while (++i < table->philo_nbr)
		sem_post(table->s_ready);
	sem_wait(table->s_end);
	return ;
}
