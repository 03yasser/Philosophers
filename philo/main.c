/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:15:27 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/13 10:22:42 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_table **table)
{
	t_philo	*philo;
	int		i;

	philo = *(*table)->philos;
	i = -1;
	while (++i < (*table)->philo_nbr)
	{
		pthread_mutex_destroy(&philo->m_philo);
		pthread_mutex_destroy(&philo->m_fork);
		philo = philo->next;
	}
	pthread_mutex_destroy(&(*table)->m_table);
	pthread_mutex_destroy(&(*table)->m_write);
}

void	write_status(char *str, t_philo *philo, t_table *table)
{
	if (!get_var(&table->m_table, &table->end))
	{
		pthread_mutex_lock(&table->m_write);
		printf("%lu %d %s\n", get_time(table) - table->start, philo->id, str);
		pthread_mutex_unlock(&table->m_write);
	}
}

void	error1(char *msg, t_free **list_aloc)
{
	ft_putstr_fd(msg, 2);
	ft_free_all(list_aloc);
}

void	error2(char *msg, t_table *table)
{
	ft_putstr_fd(msg, 2);
	ft_clean(&table);
	ft_free_all(table->alloc);
}

int	main(int ac, char **argv)
{
	t_table		*table;
	t_free		*alloc;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("wrong number of arguments\n", 2), 1);
	alloc = NULL;
	table = NULL;
	if (input_pars(&table, argv, &alloc))
	{
		error1("wrong input", &alloc);
		return (1);
	}
	data_init(table, &alloc);
	start_simulation(table);
	ft_clean(&table);
	ft_free_all(&alloc);
	return (0);
}
