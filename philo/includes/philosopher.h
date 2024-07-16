/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:03:20 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 12:27:11 by lethomas         ###   ########.fr       */
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

/*----------------FT_UTILS-----------------*/

int		ft_atoi(const char *str, char alpha_term_allow);
int		ft_putendl_fd(char *s, int fd);
void	ft_bzero(void *b, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_putnbr_fd(int nb, int fd);
int		ft_putstr_fd(char *s, int fd);
void	*ft_memset(void *b, int c, size_t len);
int		ft_putchar_fd(char c, int fd);

#endif
