/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:03:20 by macbook           #+#    #+#             */
/*   Updated: 2023/11/23 17:47:47 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "../libft/includes/libft.h"
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

# define NO_LIMIT -1

typedef struct s_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	time_t			init_time;
}	t_info;

typedef struct s_mutex_tabs
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	io;
	pthread_mutex_t	*time_last_meal;
	pthread_mutex_t	is_a_philo_dead;
}	t_mutex_tabs;

typedef struct s_philo_thread_arg
{
	int				nb_thread;
	t_info			*info;
	t_bool			*fork_available;
	t_mutex_tabs	*mutex_tabs;
	time_t			*time_last_meal;
	t_bool			*is_a_philo_dead;
}	t_philo_arg;


int		ft_init_philo(t_info *info, pthread_t **thread_tab,
			t_mutex_tabs **mutex_tabs);
int		ft_create_philo(t_info *info, pthread_t **thread_tab, 
			t_mutex_tabs *mutex_tabs);
int		ft_end_philo(t_info *info,  pthread_t **thread_tab,
			t_mutex_tabs **mutex_tabs);

void	*ft_philo(void *arg);
int		ft_philo_thinking(t_philo_arg *arg, t_bool *is_a_philo_dead);
int		ft_philo_eating(t_philo_arg *arg, int *nb_eat_left,
			t_bool *is_a_philo_dead);
int		ft_philo_spleeping(t_philo_arg *arg, t_bool *is_a_philo_dead);
int		ft_is_a_philo_dead(t_philo_arg *arg, t_bool *is_a_philo_dead);
int		ft_print_locked(char *str, t_philo_arg *arg, t_bool *is_a_philo_dead);

int		ft_get_time(time_t *time_int);

#endif
