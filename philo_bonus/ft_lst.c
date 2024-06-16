/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:04:10 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/13 10:26:08 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_lstlast(t_philo *lst)
{
	t_philo	*p;

	if (!lst)
		return (NULL);
	p = lst;
	while (p -> next)
		p = p -> next;
	return (p);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new_node)
{
	t_philo	*p;

	p = NULL;
	if (!lst || !new_node)
		return ;
	if (!(*lst))
		*lst = new_node;
	else
	{
		p = ft_lstlast(*lst);
		p -> next = new_node;
	}
}
