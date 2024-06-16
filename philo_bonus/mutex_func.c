/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:57:20 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/15 08:57:00 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_var(sem_t *s, int *dest, int value)
{
	sem_wait(s);
	*dest = value;
	sem_post(s);
}

int	get_var(sem_t *s, int *value)
{
	int	ret;

	sem_wait(s);
	ret = *value;
	sem_post(s);
	return (ret);
}
