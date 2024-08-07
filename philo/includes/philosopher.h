/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:03:20 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/24 14:21:34 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

/*-------------------INCLUDE-------------------*/

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>

/*--------------------MACRO--------------------*/

# define NO_LIMIT -1

/*-----------------STRUCT-ENUM-----------------*/

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_info
{
	int				count;
	int				starv_time;
	int				eat_time;
	int				sleep_time;
	int				meal_left;
}	t_info;

typedef struct s_mutex
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*last_meal;
	pthread_mutex_t	*meal_left;
	pthread_mutex_t	must_stop;
}	t_mutex;

typedef struct s_philo
{
	int				nb;
	int				count;
	time_t			sleep_time;
	time_t			starv_time;
	time_t			eat_time;
	int				meal_left;
	time_t			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*m_io;
	pthread_mutex_t	*m_cs;
	pthread_mutex_t	*m_ms;
	pthread_mutex_t	*m_lm;
	pthread_mutex_t	*m_ml;
	time_t			start_time;
	t_bool			*must_stop;
}	t_philo;

/*----------------PROGRAM_STEP-----------------*/

int		init_data(t_info info, t_bool *must_stop, t_philo **philo,
			t_mutex *mutex);
int		create_thread(int count, t_philo *philo);
int		free_destroy(int count, t_philo *philo, t_mutex *mutex);

/*---------------THREAD_ROUTINE----------------*/

void	*philo_routine(void *philo);
void	*reaper_routine(void *philo_void);

/*----------------THREAD_UTILS-----------------*/

int		philo_usleep(time_t wait_time, t_bool *must_stop,
			pthread_mutex_t *mutex);
int		print_locked(char *str, t_philo *philo, t_bool is_reaper);
int		get_time(time_t *time_int);

int		set_must_stop(t_bool new_val, t_bool *must_stop,
			pthread_mutex_t *stop_mutex);
int		get_must_stop(t_bool *to_get, t_bool *getted, pthread_mutex_t *mutex);

/*----------------FT_UTILS-----------------*/

int		ft_atoi(const char *str, char alpha_term_allow);
int		ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int nb, int fd);
int		ft_putstr_fd(char *s, int fd);
void	*ft_memset(void *b, int c, size_t len);
int		ft_putchar_fd(char c, int fd);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *b, size_t n);

#endif
