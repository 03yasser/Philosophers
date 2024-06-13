/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:46:03 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/13 09:32:43 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static int	is_whitespace(char c)
{
	int		i;
	char	*set;

	i = 0;
	set = " \t\n\v\f\r";
	while (set[i])
	{
		if (c == set[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_substr(char const *s, int start, int len, t_free **ptrs)
{
	int		i;
	char	*subs;

	if (!s)
		return (NULL);
	if (!len)
		return (NULL);
	subs = ft_malloc(ptrs, len + 1);
	i = 0;
	while (i < len && s[start])
	{
		subs[i] = s[start];
		start++;
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

char	*trim_str(char *str, t_free **alloc)
{
	int		i;
	int		start;
	int		new_len;
	char	*result;

	i = 0;
	new_len = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	while (str[i] && !is_whitespace(str[i]))
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	start = i--;
	while (str[++i])
		new_len++;
	while (--i >= 0 && !is_whitespace(str[i]))
		new_len--;
	result = ft_substr(str, start, new_len, alloc);
	return (result);
}


int	ft_atoi(char *str, t_free **alloc)
{
	int		i;
	int		n;
	char	*trimed_str;

	i = 0;
	n = 0;
	if (!str || !str[0])
		return (0);
	trimed_str = trim_str(str, alloc);
	if (!trimed_str || trimed_str[0] == '-')
		error1("wrong input\n", alloc);
	if (trimed_str[i] == '+')
		i++;
	while (trimed_str[i])
	{
		if (ft_isdigit(trimed_str[i]))
			error1("wrong input\n", alloc);	
		n = (n * 10) + (trimed_str[i] - 48);
		if (n < 0)
			error1("wrong input\n", alloc);
		i++;
	}
	ft_free_ptr(alloc, trimed_str);
	return (n);
}

int	input_pars(t_table **table, char **argv, t_free **alloc)
{
	*(table) = ft_malloc(alloc, sizeof(t_table));
	(*table)->philo_nbr = ft_atoi(argv[1], alloc);
	if ((*table)->philo_nbr < 1 || (*table)->philo_nbr > 200)
		return (1);
	(*table)->t_to_die = ft_atoi(argv[2], alloc);
	if ((*table)->t_to_die == 0)
		return (1);
	(*table)->t_to_eat = ft_atoi(argv[3], alloc);
	if ((*table)->t_to_eat == 0)
		return (1);
	(*table)->t_to_sleep = ft_atoi(argv[4], alloc);
	if ((*table)->t_to_sleep == 0)
		return (1);
	if (argv[5] == NULL)
		(*table)->limit_meals = -1;
	else 
		(*table)->limit_meals = ft_atoi(argv[5], alloc);
	if ((*table)->limit_meals == 0)
		return (1);
	return (0);
}
