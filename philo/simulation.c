/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:02:44 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/13 10:24:17 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_fork);
	write_status("has taken a fork", philo, philo->table);
	pthread_mutex_lock(&philo->next->m_fork);
	write_status("has taken a fork", philo, philo->table);
	pthread_mutex_lock(&philo->m_philo);
	philo->last_eat = get_time(philo->table) - philo->table->start;
	pthread_mutex_unlock(&philo->m_philo);
	philo->meals_counter++;
	write_status("is eating", philo, philo->table);
	ft_usleep(philo->table->t_to_eat, philo->table);
	pthread_mutex_unlock(&(philo->m_fork));
	pthread_mutex_unlock(&(philo->next->m_fork));
	if (philo->table->limit_meals != -1
		&& philo->meals_counter == philo->table->limit_meals)
		set_var(&philo->m_philo, &philo->full, 1);
}

static void	*philo_routine(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	while (!get_var(&table->m_table, &table->ready))
		usleep(500);
	if (philo->id % 2 == 1)
		usleep(500);
	pthread_mutex_lock(&philo->m_philo);
	philo->last_eat = get_time(table) - table->start;
	pthread_mutex_unlock(&philo->m_philo);
	while (!get_var(&table->m_table, &table->end))
	{
		write_status("is thinking", philo, table);
		eat(philo);
		write_status("is sleeping", philo, table);
		ft_usleep(table->t_to_sleep, table);
	}
	return (NULL);
}

static void	*philo_1(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!get_var(&philo->table->m_table, &philo->table->ready))
		usleep(500);
	pthread_mutex_lock(&philo->m_philo);
	philo->last_eat = get_time(philo->table) - philo->table->start;
	pthread_mutex_unlock(&philo->m_philo);
	write_status("is thinking", philo, philo->table);
	pthread_mutex_lock(&philo->m_fork);
	write_status("has taken a fork", philo, philo->table);
	while (!get_var(&philo->table->m_table, &philo->table->end))
		usleep(1000);
	return (NULL);
}

void	simulation_utils(t_table *table)
{
	int		i;
	t_philo	*philo;
	t_philo	*p;

	philo = *(table->philos);
	i = -1;
	while (++i < table->philo_nbr && philo)
	{
		p = philo;
		pthread_create(&philo->philo, NULL, philo_routine, p);
		philo = philo->next;
	}
}

void	start_simulation(t_table *table)
{
	int		i;
	t_philo	*philo;
	t_philo	*p;

	philo = *(table->philos);
	p = philo;
	if (table->philo_nbr == 1)
		pthread_create(&philo->philo, NULL, philo_1, p);
	else
		simulation_utils(table);
	pthread_create(&table->monitor, NULL, waiter_routine, table);
	table->start = get_time(table);
	set_var(&table->m_table, &table->ready, 1);
	i = -1;
	while (++i < table->philo_nbr && p)
	{
		pthread_join(p->philo, NULL);
		p = p->next;
	}
	pthread_join(table->monitor, NULL);
}
