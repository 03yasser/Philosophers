/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:46:42 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/13 09:33:41 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_free
{
	void			*ptr;
	struct s_free	*next;
}	t_free;


typedef struct s_philo
{
	pthread_t			philo;
	pthread_mutex_t		m_fork;
	pthread_mutex_t		m_philo;
	int					id;
	int					meals_counter;
	int					fork_locked;
	int					full;
	size_t				last_eat;
	struct	s_table		*table;
	struct	s_philo		*next;
}				t_philo;

typedef struct	s_table
{
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				threads_runing;
	int				limit_meals;
	int				philo_nbr;
	int				ready;
	int				end;
	size_t			start;
	t_free			**alloc;
	pthread_t		monitor;
	t_philo			**philos;
	pthread_mutex_t	m_table;
	pthread_mutex_t	m_write;
}				t_table;

int		ft_strlen(char *s);
int		ft_isdigit(int c);
int		ft_usleep(size_t milliseconds, t_table *table);
int		ft_atoi(char *str, t_free **alloc);
void	ft_putstr_fd(char *s, int fd);
char	*trim_str(char *str, t_free **alloc);
void	*ft_malloc(t_free **list_aloc, size_t size);
void	ft_free_all(t_free **list_aloc);
char	*ft_strdup(char *str, t_free **alloc);
int		ft_strlen(char *s);
void	error1(char *msg, t_free **list_aloc);
void	error2(char *msg, t_table *table);
void	ft_free_ptr(t_free **list_aloc, void *ptr);
void	ft_lstadd_back(t_philo **lst, t_philo *new_node);
size_t	get_time(t_table *table);
int		get_var(pthread_mutex_t *mutex, int *value);
void	set_var(pthread_mutex_t *mutex, int *dest, int value);
void	ft_putstr_fd(char *s, int fd);
void	data_init(t_table *table, t_free **alloc);
int		input_pars(t_table **table, char **argv, t_free **alloc);
void	start_simulation(t_table *table);
void	ft_clean(t_table **table);
int		ft_strcmp(const char *s1, const char *s2);
void	write_status(char *str, t_philo *philo, t_table *table);
#endif