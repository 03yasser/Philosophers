/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:02:44 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/16 14:49:07 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_table *table)
{
	t_philo	*philo;

	philo = table->philo;
	sem_wait(table->s_forks);
	write_status("has taken a fork", philo, table);
	sem_wait(table->s_forks);
	write_status("has taken a fork", philo, table);
	philo->last_eat = get_time(table) - table->start;
	philo->meals_counter++;
	write_status("is eating", philo, table);
	ft_usleep(table->t_to_eat, table);
	sem_post(table->s_forks);
	sem_post(table->s_forks);
	if (table->limit_meals != -1
		&& philo->meals_counter == table->limit_meals)
		philo->full = 1;
}

static void	*philo_routine(t_table *table)
{
	char	*str;
	int		i;
	int		id;

	sem_wait(table->s_ready);
	printf("current time %lu\n", get_time(table));
	// printf("start %lu\n", table->start);
	// if (philo->id % 2 == 1)
	// 	usleep(100);
	// i = -1;
	// id  = philo->id;
	// str = ft_malloc(table->alloc, 4);
	// while (id > 0 && i < 9)
	// {
	// 	str[++i] = 48 + philo->id % 10;
	// 	id /= 10;
	// }
	// sem_unlink(str);
	// philo->s_philo = sem_open(str, O_CREAT, 0600, 1);
	// ft_free_ptr(table.alloc, str);
	// pthread_create(&philo->philo, NULL, waiter_routine, philo);
	// sem_wait(philo->s_philo);
	// philo->last_eat = get_time(&table) - table.start;
	// sem_post(philo->s_philo);
	// while (!get_var(philo->s_philo, &philo->end))
	// {
		// write_status("is thinking", philo, table);
		// eat(table);
		// write_status("is sleeping", philo, table);
		// ft_usleep(table->t_to_sleep, table);
	// }
	ft_clean(table);
	ft_free_all(table->alloc);
	exit(0);
	return (NULL);
}

// static void	*philo_1(t_philo *philo)
// {
// 	t_philo	*philo;

// 	sem_wait(philo->table.s_ready);
// 	philo->last_eat = get_time(philo->table) - philo->table->start;
// 	write_status("is thinking", philo, philo->table);
// 	write_status("has taken a fork", philo, philo->table);
// 	sem_wait(philo->table->end);
// 	sem_wait(philo->table->s_write);
// 	printf("%lu %d died\n", time - table->start, philo->id);
// 	while (!get_var(&philo->table->, &philo->table->end))
// 		usleep(1000);
// 	return (NULL);
// }

void	simulation_utils(t_table *table)
{
	int		i;
	int		pid;
	t_philo	*philo;

	i = -1;
	philo = table->philo;
	
	while (++i < table->philo_nbr)
	{
		philo->id = i + 1;
		pid = fork();
		if (pid == 0)
			philo_routine(table);
	}
}

void	start_simulation(t_table *table)
{
	int		i;

	// if (table->philo_nbr == 1)
	// 	pthread_create(&philo->philo, NULL, philo_1, p);
	// else
	simulation_utils(table);
	i = -1;
	table->start = get_time(table);
	while (++i < table->philo_nbr)
		sem_post(table->s_ready);
	while (waitpid(0, NULL, 0) == -1)
		;
	ft_clean(table);
	return ;
}
