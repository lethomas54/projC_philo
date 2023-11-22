/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 03:08:52 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/21 23:17:04 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_print_locked(char *str, t_philo_info *philo_info,
	t_mutex_tabs *mutex_tabs, int nb_thread, t_bool *is_a_philo_dead_addr)
{
	time_t			time;
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
		if (ft_get_time(&time))
			return (EXIT_FAILURE);
		time_stamp = time - philo_info->init_time;
		if (printf("%d %d %s\n", (int)time_stamp, nb_thread + 1, str) == -1)
			return (EXIT_FAILURE);
		if (pthread_mutex_unlock(&mutex_tabs->io))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_philo_spleeping(t_philo_info *philo_info, t_mutex_tabs *mutex_tabs,
	int nb_thread, t_bool *is_a_philo_dead_addr)
{
	if (ft_print_locked("is sleeping", philo_info, mutex_tabs, nb_thread, is_a_philo_dead_addr))
		return (EXIT_FAILURE);
	if (usleep((useconds_t)(1000 * philo_info->time_to_sleep)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_philo_thinking(t_philo_info *philo_info, t_mutex_tabs *mutex_tabs,
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
