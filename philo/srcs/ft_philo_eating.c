/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_eating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:41:37 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/05 13:52:26 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_get_a_fork(t_philo_arg *arg, int nb_fork,
	t_bool *is_a_philo_dead)
{
	t_bool	have_his_fork;

	have_his_fork = false;
	while (have_his_fork == false && *is_a_philo_dead == false)
	{
		if (pthread_mutex_lock(arg->mutex_tabs->fork + nb_fork))
			return (EXIT_FAILURE);
		if (arg->fork_available[nb_fork] == true)
		{
			arg->fork_available[nb_fork] = false;
			have_his_fork = true;
			if (ft_print_locked("has taken a fork", arg, is_a_philo_dead))
				return (EXIT_FAILURE);
		}
		if (pthread_mutex_unlock(arg->mutex_tabs->fork + nb_fork))
			return (EXIT_FAILURE);
		if (ft_is_a_philo_dead(arg, is_a_philo_dead))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_philo_get_forks(t_philo_arg *arg, t_bool *is_a_philo_dead)
{
	if (ft_get_a_fork(arg,
			(arg->nb_thread + (arg->nb_thread % 2 == 0)) % arg->info.nb_philo,
			is_a_philo_dead))
		return (EXIT_FAILURE);
	if (*is_a_philo_dead == true)
		return (EXIT_SUCCESS);
	if (ft_get_a_fork(arg,
			(arg->nb_thread + (arg->nb_thread % 2 != 0)) % arg->info.nb_philo,
			is_a_philo_dead))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_philo_let_forks(t_philo_arg *arg)
{
	if (pthread_mutex_lock(arg->mutex_tabs->fork
			+ (arg->nb_thread + (arg->nb_thread % 2 == 0))
			% arg->info.nb_philo))
		return (EXIT_FAILURE);
	arg->fork_available[(arg->nb_thread + (arg->nb_thread % 2 == 0))
		% arg->info.nb_philo] = true;
	if (pthread_mutex_unlock(arg->mutex_tabs->fork
			+ (arg->nb_thread + (arg->nb_thread % 2 == 0))
			% arg->info.nb_philo))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(arg->mutex_tabs->fork + (arg->nb_thread
				+ (arg->nb_thread % 2 != 0)) % arg->info.nb_philo))
		return (EXIT_FAILURE);
	arg->fork_available[(arg->nb_thread + (arg->nb_thread % 2 != 0))
		% arg->info.nb_philo] = true;
	if (pthread_mutex_unlock(arg->mutex_tabs->fork + (arg->nb_thread
				+ (arg->nb_thread % 2 != 0)) % arg->info.nb_philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_update_last_meal_time(time_t *time_since_last_meal,
	t_bool *is_a_philo_dead)
{
	if (*is_a_philo_dead == true)
		return (EXIT_SUCCESS);
	if (ft_get_time(time_since_last_meal))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_philo_eating(t_philo_arg *arg, int *nb_eat_left, t_bool *is_a_philo_dead)
{
	if (ft_philo_get_forks(arg, is_a_philo_dead))
		return (EXIT_FAILURE);
	if (ft_update_last_meal_time(arg->time_last_meal, is_a_philo_dead))
		return (EXIT_FAILURE);
	if (ft_print_locked("is eating", arg, is_a_philo_dead))
		return (EXIT_FAILURE);
	if (ft_philo_usleep(arg, arg->info.time_to_eat, is_a_philo_dead))
		return (EXIT_FAILURE);
	if (ft_philo_let_forks(arg))
		return (EXIT_FAILURE);
	*nb_eat_left -= (*nb_eat_left != NO_LIMIT);
	return (EXIT_SUCCESS);
}
