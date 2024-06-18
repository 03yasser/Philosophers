/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:46:42 by yboutsli          #+#    #+#             */
/*   Updated: 2024/06/18 21:24:21 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_free
{
	void			*ptr;
	struct s_free	*next;
}	t_free;

typedef struct s_philo
{
	pthread_t			philo;
	int					pid;
	int					id;
	int					meals_counter;
	int					full;
	int					end;
	size_t				last_eat;
	struct s_table		*table;
	struct s_philo		*next;
}				t_philo;

typedef struct s_table
{
	pthread_t		t_table;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				limit_meals;
	int				philo_nbr;
	size_t			start;
	t_free			**alloc;
	sem_t			*s_ready;
	sem_t			*s_forks;
	sem_t			*s_end;
	sem_t			*s_stop;
	sem_t			*s_write;
	sem_t			*s_full;	
	t_philo			*philo;
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
void	ft_putstr_fd(char *s, int fd);
t_philo	*init(t_table *table, t_free **alloc);
t_table	input(char **argv, t_free **alloc);
void	start_simulation(t_table *table, t_philo **philo);
void	ft_clean(t_table *table, t_philo **philo);
int		ft_strcmp(const char *s1, const char *s2);
void	write_status(char *str, t_philo *philo, t_table *table);
char	*ft_strdup(char *str, t_free **ptrs);
int		check_input(t_table table);
t_philo	*create_philo(t_free **alloc);
#endif