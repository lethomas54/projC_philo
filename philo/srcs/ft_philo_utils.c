/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 10:29:46 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/04 13:29:33 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_print_locked(char *str, t_philo_arg *arg, t_bool *is_a_philo_dead)
{
	time_t	time;

	if (is_a_philo_dead != NULL)
	{
		if (pthread_mutex_lock(&arg->mutex_tabs->is_a_philo_dead))
			return (EXIT_FAILURE);
		*is_a_philo_dead = *arg->is_a_philo_dead;
	}
	if (is_a_philo_dead == NULL || *is_a_philo_dead == false)
	{
		if (pthread_mutex_lock(&arg->mutex_tabs->io))
			return (EXIT_FAILURE);
		if (ft_get_time(&time))
			return (EXIT_FAILURE);
		if (printf("%d %d %s\n", (int)(time - arg->info->init_time),
			arg->nb_thread + 1, str) == -1)
			return (EXIT_FAILURE);
		if (pthread_mutex_unlock(&arg->mutex_tabs->io))
			return (EXIT_FAILURE);
	}
	if (is_a_philo_dead != NULL)
		if (pthread_mutex_unlock(&arg->mutex_tabs->is_a_philo_dead))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_philo_usleep(t_philo_arg *arg, time_t time_to_usleep,
	t_bool *is_a_philo_dead)
{
	time_t	time_start;
	time_t	time;

	if (ft_get_time(&time_start))
		return (EXIT_FAILURE);
	time = time_start;
	while (time - time_start < time_to_usleep
		&& *is_a_philo_dead == false)
	{
		if (usleep((useconds_t)(100)))
			return (EXIT_FAILURE);
		if (ft_is_a_philo_dead(arg, is_a_philo_dead))
			return (EXIT_FAILURE);
		if (ft_get_time(&time))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_is_himself_dead(t_philo_arg *arg, t_bool *is_a_philo_dead)
{
	time_t	time;

	if (ft_get_time(&time))
		return (EXIT_FAILURE);
	time -= *arg->time_last_meal;
	if (time >= arg->info->time_to_die)
		*is_a_philo_dead = true;
	if (*is_a_philo_dead == true)
	{
		*arg->is_a_philo_dead = true;
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
	if (*is_a_philo_dead == false)
		if (ft_is_himself_dead(arg, is_a_philo_dead))
			return (EXIT_FAILURE);
	if (pthread_mutex_unlock(&arg->mutex_tabs->is_a_philo_dead))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
