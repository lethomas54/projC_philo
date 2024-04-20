/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:17:16 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/12 14:36:15 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_init_mutex(t_info info, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < info.philo_count)
	{
		if (pthread_mutex_init(mutex->fork + i, NULL))
			return (EXIT_FAILURE);
		if (pthread_mutex_init(mutex->meal_upd + i++, NULL))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&mutex->io, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_init_elem(int nb, t_info info, t_mutex *mutex, t_philo *philo)
{
	philo[nb].nb = nb;
	philo[nb].philo_count = info.philo_count;
	philo[nb].eat_time = info.eat_time;
	philo[nb].sleep_time = info.sleep_time;
	philo[nb].starv_time = info.starv_time;
	philo[nb].meal_left = info.meal_left;
	philo[nb].last_meal = 0;
	if (nb == 0)
		philo[nb].left_fork = &mutex->fork[info.philo_count - 1];
	else
		philo[nb].left_fork = mutex->fork + nb - 1;
	philo[nb].right_fork = mutex->fork + nb;
	philo[nb].io = &mutex->io;
	philo[nb].meal_upd = mutex->meal_upd + nb;
	return (EXIT_SUCCESS);
}

void	ft_set_shared_ressource(t_shared *shared)
{
	shared->can_start = false;
	shared->must_stop = false;
	shared->start_time = 0;
}

int	ft_init_philo(t_info info, t_shared *sh, t_philo **philo, t_mutex *mutex)
{
	int	i;

	i = 0;
	ft_bzero(mutex, sizeof(t_mutex));
	*philo = (t_philo *)ft_calloc(info.philo_count, sizeof(t_philo));
	if (*philo == NULL)
		return (EXIT_FAILURE);
	mutex->fork = (pthread_mutex_t *)ft_calloc(info.philo_count,
			sizeof(pthread_mutex_t));
	if (mutex->fork == NULL)
		return (EXIT_FAILURE);
	mutex->meal_upd = (pthread_mutex_t *)ft_calloc(info.philo_count,
			sizeof(pthread_mutex_t));
	if (mutex->meal_upd == NULL)
		return (EXIT_FAILURE);
	if (ft_init_mutex(info, mutex))
		return (EXIT_FAILURE);
	ft_set_shared_ressource(sh);
	while (i < info.philo_count)
	{
		(*philo)[i].shared = sh;
		if (ft_init_elem(i++, info, mutex, *philo))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
