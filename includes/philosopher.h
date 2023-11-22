/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:03:20 by macbook           #+#    #+#             */
/*   Updated: 2023/11/22 01:25:13 by lethomas         ###   ########.fr       */
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

typedef struct s_philo_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	time_t			init_time;
}	t_philo_info;

typedef struct s_mutex_tabs
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	io;
	pthread_mutex_t	*time_last_meal;
	pthread_mutex_t	*nb_must_eat;
	pthread_mutex_t	is_a_philo_dead;
}	t_mutex_tabs;

typedef struct s_philo_thread_arg
{
	int				nb_thread;
	t_philo_info	*philo_info;
	t_bool			*fork_available;
	t_mutex_tabs	*mutex_tabs;
	time_t			*time_last_meal;
	t_bool			*is_a_philo_dead;
}	t_philo_thread_arg;

typedef struct s_death_thread_arg
{
	time_t			**time_last_meal;
	int				**nb_must_eat;
	t_philo_info	philo_info;
	t_mutex_tabs	*mutex_tabs;
	t_bool			*is_a_philo_dead;
}	t_death_thread_arg;

int		ft_set_philo_info(int argc, char **argv, t_philo_info *philo_info);

int 	ft_philo_start(t_philo_info philo_info, pthread_t **thread_tab,
			t_mutex_tabs **mutex_tabs);
int		ft_init_philo(t_philo_info philo_info, pthread_t **thread_tab,
			t_mutex_tabs **mutex_tabs);

void	*ft_philo(void *arg);

int		ft_philo_eating(t_philo_thread_arg *arg);
int		ft_philo_spleeping(t_philo_info *philo_info, t_mutex_tabs *mutex_tabs,
			int nb_thread, t_bool *is_a_philo_dead_addr);
int		ft_philo_thinking(t_philo_info *philo_info, t_mutex_tabs *mutex_tabs,
			int nb_thread, t_bool *is_a_philo_dead_addr);
int		ft_is_a_philo_dead(t_mutex_tabs *mutex_tabs, t_bool *is_a_philo_dead,
			t_bool *is_a_philo_dead_addr);
int		ft_update_last_meal_time(int nb_thread, t_mutex_tabs *mutex_tabs,
			time_t *time_since_last_meal);
int		ft_print_locked(char *str, t_philo_info *philo_info,
			t_mutex_tabs *mutex_tabs, int nb_thread, t_bool *is_a_philo_dead_addr);

void	*ft_death(void *thread_arg);

int		ft_create_thread(t_philo_info philo_info, pthread_t **thread_tab, 
			t_mutex_tabs *mutex_tabs);
int		ft_thread_join(t_philo_info philo_info, pthread_t **thread_tab);
int		ft_destroy_mutex_tab(t_philo_info philo_info, t_mutex_tabs **mutex_tabs);

int		ft_get_time(time_t *time_int);

#endif
