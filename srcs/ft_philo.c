/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:32:58 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/21 22:44:41 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_philo_simu(t_philo_thread_arg *arg)
{
	t_bool	is_a_philo_dead;
	
	is_a_philo_dead = false;
	while (arg->philo_info->nb_must_eat != 0
			&& is_a_philo_dead == false)
	{
		if (is_a_philo_dead == false && ft_philo_thinking(arg->philo_info,
			arg->mutex_tabs, arg->nb_thread, arg->is_a_philo_dead))
			return (EXIT_FAILURE);
		if (is_a_philo_dead == false && ft_philo_eating(arg))
			return (EXIT_FAILURE);
		if (is_a_philo_dead == false && ft_is_a_philo_dead(arg->mutex_tabs,
			&is_a_philo_dead, arg->is_a_philo_dead))
			return (EXIT_FAILURE);
		if (is_a_philo_dead == false && ft_philo_spleeping(arg->philo_info,
			arg->mutex_tabs, arg->nb_thread, arg->is_a_philo_dead))
			return (EXIT_FAILURE);
		if (is_a_philo_dead == false && ft_is_a_philo_dead(arg->mutex_tabs,
			&is_a_philo_dead, arg->is_a_philo_dead))
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
	if (ft_philo_simu(thread_arg))
		return_value = EXIT_FAILURE;
	free(thread_arg->philo_info);
	free(thread_arg->time_last_meal);
	free(thread_arg);
	return (NULL);
}
