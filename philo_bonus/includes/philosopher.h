/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:03:20 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/09 00:46:04 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "../../libft/includes/libft.h"
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>

# define NO_LIMIT -1
# define PHILO_DEAD 42

typedef struct s_info
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_must_eat;
	time_t	init_time;
}	t_info;

typedef struct s_sem_tab
{
	sem_t	*fork_first;
	sem_t	*fork_scnd;
	sem_t	*io;
}	t_sem_tab;

typedef struct s_philo
{
	int				nb_process;
	t_sem_tab		*sem_tab;
	t_info			*info;
	time_t			last_meal_time;
	pthread_mutex_t	mutex_death;
	int				nb_meal_left;
}	t_philo;

int		ft_set_info(int argc, char **argv, t_info *info);
int		ft_open_sem_tab(t_info info, t_sem_tab *sem_tab);
int		ft_create_children(t_info info, t_sem_tab *sem_tab, pid_t **child_pid,
			t_bool *is_main_process);
int		ft_wait_for_children(t_info info, pid_t **child_pid,
			int global_return_value);
int		ft_close_sem_tab(t_sem_tab *sem_tab, t_bool is_main_process);

int		ft_philo(t_philo *philo);

int		ft_philo_thinking(t_philo *philo);
int		ft_philo_eating(t_philo *philo);
int		ft_philo_sleeping(t_philo *philo);

int		ft_philo_usleep(time_t time_to_usleep);
int		ft_print_locked(char *str, t_philo *philo, t_bool do_sem_post);
int		ft_get_nb_must_eat(t_philo *philo, int *nb_must_eat);

void	*ft_death(void *info);

int		ft_get_time(time_t *time_int);

#endif
