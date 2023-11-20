/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:32:58 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/20 16:08:31 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_update_last_meal_time(int nb_thread,
	t_mutex_tabs *mutex_tabs, struct timeval *time_since_last_meal)
{
	if (pthread_mutex_lock(mutex_tabs->time_last_meal + nb_thread))
		return (EXIT_FAILURE);
	if (gettimeofday(time_since_last_meal, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(mutex_tabs->time_last_meal + nb_thread))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_philo_simu(t_philo_thread_arg *thread_arg)
{
	t_bool	is_a_philo_dead;
	
	is_a_philo_dead = false;
	while (thread_arg->philo_info->nb_must_eat != 0
			&& is_a_philo_dead == false)
	{
		if (ft_philo_is_thinking(thread_arg->philo_info, thread_arg->mutex_tabs,
			thread_arg->nb_thread, thread_arg->is_a_philo_dead))
			return (EXIT_FAILURE);
		if (ft_philo_is_eating(thread_arg->philo_info, thread_arg->mutex_tabs,
			thread_arg->nb_thread, thread_arg->time_last_meal, thread_arg->is_a_philo_dead))
			return (EXIT_FAILURE);
		if (ft_philo_is_spleeping(thread_arg->philo_info, thread_arg->mutex_tabs,
			thread_arg->nb_thread, thread_arg->is_a_philo_dead))
			return (EXIT_FAILURE);
		if (ft_is_a_philo_dead(thread_arg->mutex_tabs, &is_a_philo_dead,
			thread_arg->is_a_philo_dead))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	*ft_philo(void *thread_arg_void)
{
	int					return_value;
	t_philo_thread_arg	*thread_arg;

	return_value = EXIT_SUCCESS;
	thread_arg = (t_philo_thread_arg *)thread_arg_void;
	if (return_value == EXIT_SUCCESS)
		if (ft_philo_simu(thread_arg))
			return_value = EXIT_FAILURE;
	free(thread_arg->philo_info);
	free(thread_arg->time_last_meal);
	free(thread_arg);
	return (NULL);
}
