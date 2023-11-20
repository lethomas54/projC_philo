/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 03:08:52 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/20 15:42:46 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_print_locked(char *str, t_philo_info *philo_info,
	t_mutex_tabs *mutex_tabs, int nb_thread, t_bool *is_a_philo_dead_addr)
{
	struct timeval	time;
	time_t			time_stamp;
	t_bool			is_a_philo_dead;
	
	is_a_philo_dead = false;
	if (is_a_philo_dead_addr != NULL)
	{
		if (ft_is_a_philo_dead(mutex_tabs, &is_a_philo_dead,
			is_a_philo_dead_addr))
			return (EXIT_FAILURE);
	}
	if (is_a_philo_dead == false)
	{
		if (pthread_mutex_lock(&mutex_tabs->io))
			return (EXIT_FAILURE);
		if (gettimeofday(&time, NULL))
			return (EXIT_FAILURE);
		time_stamp = 1000 * (time.tv_sec - philo_info->init_time.tv_sec)
			+ (time.tv_usec  - philo_info->init_time.tv_usec) / 1000;
		if (printf("%d %d %s\n", (int)time_stamp, nb_thread + 1, str) == -1)
			return (EXIT_FAILURE);
		if (pthread_mutex_unlock(&mutex_tabs->io))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_philo_is_eating(t_philo_info *philo_info, t_mutex_tabs *mutex_tabs,
	int nb_thread, struct timeval *time_since_last_meal, t_bool *is_a_philo_dead_addr)
{
	if (pthread_mutex_lock(mutex_tabs->fork
		+ ft_ternary_op(nb_thread != philo_info->nb_philo - 1, nb_thread, 0)))
		return (EXIT_FAILURE);
	if (ft_print_locked("has taken a fork", philo_info, mutex_tabs, nb_thread, is_a_philo_dead_addr))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(mutex_tabs->fork + ft_ternary_op(nb_thread 
		!= philo_info->nb_philo - 1, nb_thread + 1, nb_thread)))
		return ( EXIT_FAILURE);
	if (ft_print_locked("has taken a fork", philo_info, mutex_tabs, nb_thread, is_a_philo_dead_addr))
		return (EXIT_FAILURE);
	if (ft_update_last_meal_time(nb_thread,mutex_tabs, time_since_last_meal))
		return (EXIT_FAILURE);
	if (ft_print_locked("is eating", philo_info, mutex_tabs, nb_thread, is_a_philo_dead_addr))
		return (EXIT_FAILURE);
	if (usleep((useconds_t)(1000 * philo_info->time_to_eat)))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(mutex_tabs->fork
		+ ft_ternary_op(nb_thread != philo_info->nb_philo - 1, nb_thread, 0)))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(mutex_tabs->fork + ft_ternary_op(nb_thread
		!= philo_info->nb_philo - 1, nb_thread + 1, nb_thread)))
		return (EXIT_FAILURE);
	if (ft_update_last_meal_time(nb_thread,mutex_tabs, time_since_last_meal))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(mutex_tabs->nb_must_eat + nb_thread))
		return (EXIT_FAILURE);
	if (philo_info->nb_must_eat != NO_LIMIT)
		(philo_info->nb_must_eat)--;
	if (pthread_mutex_unlock(mutex_tabs->nb_must_eat + nb_thread))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_philo_is_spleeping(t_philo_info *philo_info, t_mutex_tabs *mutex_tabs,
	int nb_thread, t_bool *is_a_philo_dead_addr)
{
	if (ft_print_locked("is sleeping", philo_info, mutex_tabs, nb_thread, is_a_philo_dead_addr))
		return (EXIT_FAILURE);
	if (usleep((useconds_t)(1000 * philo_info->time_to_sleep)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_philo_is_thinking(t_philo_info *philo_info, t_mutex_tabs *mutex_tabs,
	int nb_thread, t_bool *is_a_philo_dead_addr)
{
	if (ft_print_locked("is thinking", philo_info, mutex_tabs, nb_thread, is_a_philo_dead_addr))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_is_a_philo_dead(t_mutex_tabs *mutex_tabs, t_bool *is_a_philo_dead,
	t_bool *is_a_philo_dead_addr)
{
	if (pthread_mutex_lock(&mutex_tabs->is_a_philo_dead))
		return (EXIT_FAILURE);
	*is_a_philo_dead = *is_a_philo_dead_addr;
	if (pthread_mutex_unlock(&mutex_tabs->is_a_philo_dead))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

