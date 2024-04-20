/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:03:20 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/12 18:17:07 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

/*-------------------INCLUDE-------------------*/

# include "../../libft/includes/libft.h"
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

/*--------------------MACRO--------------------*/

# define NO_LIMIT -1

/*-------------------STRUCT--------------------*/

typedef struct s_info
{
	int				philo_count;
	int				starv_time;
	int				eat_time;
	int				sleep_time;
	int				meal_left;
}	t_info;

typedef struct s_mutex
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	io;
	pthread_mutex_t	*meal_upd;
}	t_mutex;

typedef struct s_shared
{
	time_t			start_time;
	t_bool			can_start;
	t_bool			must_stop;
}	t_shared;

typedef struct s_philo
{
	int				nb;
	int				philo_count;
	int				sleep_time;
	int				starv_time;
	int				eat_time;
	int				meal_left;
	int				last_meal;
	time_t			start_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*io;
	pthread_mutex_t	*meal_upd;
	t_shared		*shared;
}	t_philo;

/*----------------PROGRAM_STEP-----------------*/

int		ft_init_philo(t_info info, t_shared *sh, t_philo **philo,
			t_mutex *mutex);
int		ft_create_thread(int philo_count, t_shared *shared, t_philo *philo);
int		ft_free_destroy(int philo_count, t_philo *philo, t_mutex *mutex);

/*---------------THREAD_ROUTINE----------------*/

void	*ft_philo_routine(void *philo);
void	*ft_reaper_routine(void *philo_void);

/*----------------THREAD_UTILS-----------------*/

int		ft_philo_usleep(time_t wait_time, t_bool *must_stop);
int		ft_print_locked(char *str, t_philo *philo, t_bool is_reaper);
int		ft_get_time(time_t *time_int);

#endif
