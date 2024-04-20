/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:32:58 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/12 14:43:04 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_eating(t_philo *philo)
{
	time_t	time;

	if (pthread_mutex_lock(philo->left_fork))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(philo->right_fork))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(philo->meal_upd))
		return (EXIT_FAILURE);
	if (ft_get_time(&time))
		return (EXIT_FAILURE);
	philo->last_meal = (int)(time - philo->shared->start_time);
	if (pthread_mutex_unlock(philo->meal_upd))
		return (EXIT_FAILURE);
	if (ft_print_locked("is eating", philo, false))
		return (EXIT_FAILURE);
	if (ft_philo_usleep(philo->eat_time,
			&philo->shared->must_stop))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->left_fork))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->right_fork))
		return (EXIT_FAILURE);
	philo->meal_left -= (philo->meal_left != NO_LIMIT);
	return (EXIT_SUCCESS);
}

static int	ft_sleep_think(t_philo *philo)
{
	if (ft_print_locked("is sleeping", philo, false))
		return (EXIT_FAILURE);
	if (ft_philo_usleep(philo->sleep_time,
			&philo->shared->must_stop))
		return (EXIT_FAILURE);
	if (ft_print_locked("is thinking", philo, false))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*ft_philo_routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	while (philo->shared->can_start == false
		&& philo->shared->must_stop == false)
		continue ;
	if (philo->shared->must_stop == true)
		return ((void *)EXIT_FAILURE);
	if (philo->nb % 2 != 0)
		if (ft_philo_usleep(philo->eat_time * 0.5,
				&philo->shared->must_stop))
			return ((void *)EXIT_FAILURE);
	while (philo->meal_left != 0
		&& philo->shared->must_stop == false)
	{
		if (ft_eating(philo)
			&& philo->shared->must_stop == false)
			return ((void *)EXIT_FAILURE);
		if (ft_sleep_think(philo)
			&& philo->shared->must_stop == false)
			return ((void *)EXIT_FAILURE);
	}
	return ((void *)EXIT_SUCCESS);
}

static int	ft_has_died(t_philo *philo, t_shared *shared)
{
	time_t	time;

	if (ft_get_time(&time))
		return (EXIT_FAILURE);
	time -= shared->start_time;
	if (pthread_mutex_lock(philo->meal_upd))
		return (EXIT_FAILURE);
	if ((int)time - philo->last_meal >= philo->starv_time)
	{
		shared->must_stop = true;
		if (ft_print_locked("has died", philo, true))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(philo->meal_upd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*ft_reaper_routine(void *philo_void)
{
	int			i;
	t_philo		*philo;
	t_shared	*shared;

	i = 0;
	philo = (t_philo *)philo_void;
	shared = philo->shared;
	while (philo->shared->can_start == false
		&& philo->shared->must_stop == false)
		continue ;
	if (philo->shared->must_stop == true)
		return ((void *)EXIT_SUCCESS);
	while (shared->must_stop == false)
	{
		if (philo[i].meal_left != 0)
			if (ft_has_died(philo + i, shared))
				return ((void *)EXIT_FAILURE);
		i = (i + 1) % philo[i].philo_count;
	}
	return ((void *)EXIT_SUCCESS);
}
