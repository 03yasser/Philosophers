/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:15:27 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/16 14:05:59 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_table *table)
{
	sem_close(table->s_write);
	sem_close(table->s_forks);
	ft_free_all(table->alloc);
}

void	write_status(char *str, t_philo *philo, t_table *table)
{
	sem_wait(table->s_write);
	printf("%lu %d %s\n", get_time(table) - table->start, philo->id, str);
	sem_post(table->s_write);
}

void	error1(char *msg, t_free **list_aloc)
{
	ft_putstr_fd(msg, 2);
	ft_free_all(list_aloc);
}

// void	error2(char *msg, t_table table)
// {
// 	ft_putstr_fd(msg, 2);
// 	ft_clean(table);
// 	// ft_free_all(table.alloc);
// }

int	main(int ac, char **argv)
{
	t_table		*table;
	t_free		*alloc;


	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("wrong number of arguments\n", 2), 1);
	alloc = NULL;
	table = input(argv, &alloc);	
	if (check_input(table))
	{
		error1("wrong input", &alloc);
		return (1);
	}
	data_init(table, &alloc);
	start_simulation(table);
	ft_clean(table);
	ft_free_all(&alloc);
	return (0);
}
