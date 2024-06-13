/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:15:12 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/10 18:25:40 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_table **table)
{
	t_philo	*philo;
	int	i;

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