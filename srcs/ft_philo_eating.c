/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_eating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:41:37 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/21 23:32:17 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_get_a_fork(t_philo_thread_arg *arg, t_bool *have_his_fork,
	int nb_fork)
{
	if (pthread_mutex_lock(arg->mutex_tabs->fork + nb_fork))
		return (EXIT_FAILURE);
	if (arg->fork_available[nb_fork] == true)
	{
		arg->fork_available[nb_fork] = false;
		*have_his_fork = true;
		if (ft_print_locked("has taken a fork", arg->philo_info,
			arg->mutex_tabs, arg->nb_thread, arg->is_a_philo_dead))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(arg->mutex_tabs->fork + nb_fork))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int ft_philo_get_forks(t_philo_thread_arg *arg, t_bool *is_a_philo_dead)
{
	t_bool	have_his_first_fork;
	t_bool	have_his_second_fork;
	
	have_his_first_fork = false;
	have_his_second_fork = false;
	while(have_his_first_fork == false && *is_a_philo_dead == false)
	{
		if (ft_is_a_philo_dead(arg->mutex_tabs, is_a_philo_dead,
			arg->is_a_philo_dead))
			return (EXIT_FAILURE);
		if (*is_a_philo_dead == false && ft_get_a_fork(arg, &have_his_first_fork, 
			ft_ternary_op(arg->nb_thread != arg->philo_info->nb_philo - 1,
			arg->nb_thread, 0)))
			return (EXIT_FAILURE);
	}
	while(have_his_second_fork == false && *is_a_philo_dead == false)
	{
		if (ft_is_a_philo_dead(arg->mutex_tabs, is_a_philo_dead,
			arg->is_a_philo_dead))
			return (EXIT_FAILURE);
		if (*is_a_philo_dead == false && ft_get_a_fork(arg, &have_his_second_fork, 
			ft_ternary_op(arg->nb_thread != arg->philo_info->nb_philo - 1,
			arg->nb_thread + 1, arg->nb_thread)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int ft_philo_let_forks(t_philo_thread_arg *arg)
{
	if (pthread_mutex_lock(arg->mutex_tabs->fork
		+ ft_ternary_op(arg->nb_thread != arg->philo_info->nb_philo - 1,
		arg->nb_thread, 0)))
		return (EXIT_FAILURE);
	arg->fork_available[ft_ternary_op(arg->nb_thread
		!= arg->philo_info->nb_philo - 1, arg->nb_thread, 0)] = true;
	if (pthread_mutex_unlock(arg->mutex_tabs->fork
		+ ft_ternary_op(arg->nb_thread != arg->philo_info->nb_philo - 1,
		arg->nb_thread, 0)))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(arg->mutex_tabs->fork + ft_ternary_op(arg->nb_thread 
		!= arg->philo_info->nb_philo - 1, arg->nb_thread + 1, arg->nb_thread)))
		return ( EXIT_FAILURE);
	arg->fork_available[ft_ternary_op(arg->nb_thread != arg->philo_info->nb_philo - 1,
		arg->nb_thread + 1, arg->nb_thread)] = true;
	if (pthread_mutex_unlock(arg->mutex_tabs->fork + ft_ternary_op(arg->nb_thread
		!= arg->philo_info->nb_philo - 1, arg->nb_thread + 1, arg->nb_thread)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_update_nb_must_eat(int nb_thread,
	t_mutex_tabs *mutex_tabs, t_philo_info *philo_info)
{
	if (pthread_mutex_lock(mutex_tabs->nb_must_eat + nb_thread))
		return (EXIT_FAILURE);
	if (philo_info->nb_must_eat != NO_LIMIT)
		(philo_info->nb_must_eat)--;
	if (pthread_mutex_unlock(mutex_tabs->nb_must_eat + nb_thread))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_update_last_meal_time(int nb_thread,
	t_mutex_tabs *mutex_tabs, time_t *time_since_last_meal)
{
	if (pthread_mutex_lock(mutex_tabs->time_last_meal + nb_thread))
		return (EXIT_FAILURE);
	if (ft_get_time(time_since_last_meal))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(mutex_tabs->time_last_meal + nb_thread))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_philo_eating(t_philo_thread_arg *arg)
{
	t_bool is_a_philo_dead;

	is_a_philo_dead = false;
	if (ft_philo_get_forks(arg, &is_a_philo_dead))
		return (EXIT_FAILURE);
	if (is_a_philo_dead == true)
		return (EXIT_SUCCESS);
	if (ft_update_last_meal_time(arg->nb_thread, arg->mutex_tabs,
		arg->time_last_meal))
		return (EXIT_FAILURE);
	if (ft_print_locked("is eating", arg->philo_info,
		arg->mutex_tabs, arg->nb_thread, arg->is_a_philo_dead))
		return (EXIT_FAILURE);
	if (usleep((useconds_t)(1000 * arg->philo_info->time_to_eat)))
		return (EXIT_FAILURE);
	if (ft_philo_let_forks(arg))
		return (EXIT_FAILURE);
	if (ft_update_last_meal_time(arg->nb_thread, arg->mutex_tabs,
		arg->time_last_meal))
		return (EXIT_FAILURE);
	if (ft_update_nb_must_eat(arg->nb_thread, arg->mutex_tabs, arg->philo_info))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
