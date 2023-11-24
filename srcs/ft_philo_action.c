/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 03:08:52 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/23 18:17:18 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_print_locked(char *str, t_philo_arg *arg, t_bool *is_a_philo_dead)
{
	time_t			time;
	time_t			time_stamp;
	
	if (is_a_philo_dead != NULL
		&& *is_a_philo_dead == false)
	{
		if (ft_is_a_philo_dead(arg, is_a_philo_dead))
			return (EXIT_FAILURE);
	}
	if (is_a_philo_dead == NULL
		|| *is_a_philo_dead == false)
	{
		if (pthread_mutex_lock(&arg->mutex_tabs->io))
			return (EXIT_FAILURE);
		if (ft_get_time(&time))
			return (EXIT_FAILURE);
		time_stamp = time - arg->info->init_time;
		if (printf("%d %d %s\n",
			(int)time_stamp, arg->nb_thread + 1, str) == -1)
			return (EXIT_FAILURE);
		if (pthread_mutex_unlock(&arg->mutex_tabs->io))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_philo_spleeping(t_philo_arg *arg, t_bool *is_a_philo_dead)
{
	if (ft_print_locked("is sleeping", arg, is_a_philo_dead))
		return (EXIT_FAILURE);
	if (*is_a_philo_dead == false
		&& usleep((useconds_t)(1000 * arg->info->time_to_sleep)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_philo_thinking(t_philo_arg *arg, t_bool *is_a_philo_dead)
{
	if (ft_print_locked("is thinking", arg, is_a_philo_dead))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_is_himself_dead(t_philo_arg *arg, t_bool *is_a_philo_dead)
{
	time_t	time;
	
	if (ft_get_time(&time))
		return (EXIT_FAILURE);
	time -= *arg->time_last_meal;
	if (time > arg->info->time_to_die)
		*is_a_philo_dead = true;
	if (*is_a_philo_dead == true)
	{
		if (pthread_mutex_lock(&arg->mutex_tabs->is_a_philo_dead))
			return (EXIT_FAILURE);
		*arg->is_a_philo_dead = true;
		if (pthread_mutex_unlock(&arg->mutex_tabs->is_a_philo_dead))
			return (EXIT_FAILURE);
		if (ft_print_locked("has died", arg, NULL))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_is_a_philo_dead(t_philo_arg *arg, t_bool *is_a_philo_dead)
{
	if (pthread_mutex_lock(&arg->mutex_tabs->is_a_philo_dead))
		return (EXIT_FAILURE);
	*is_a_philo_dead = *arg->is_a_philo_dead;
	if (pthread_mutex_unlock(&arg->mutex_tabs->is_a_philo_dead))
		return (EXIT_FAILURE);
	if (*is_a_philo_dead == false)
		if (ft_is_himself_dead(arg, is_a_philo_dead))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
