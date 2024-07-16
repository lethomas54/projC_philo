/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:17:16 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 19:26:57 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	malloc_mutex_tab(t_info info, t_mutex *mutex)
{
	mutex->fork = (pthread_mutex_t *)ft_calloc(info.count,
			sizeof(pthread_mutex_t));
	if (mutex->fork == NULL)
		return (EXIT_FAILURE);
	mutex->meal_time = (pthread_mutex_t *)ft_calloc(info.count,
			sizeof(pthread_mutex_t));
	if (mutex->meal_time == NULL)
		return (EXIT_FAILURE);
	mutex->meal_count = (pthread_mutex_t *)ft_calloc(info.count,
			sizeof(pthread_mutex_t));
	if (mutex->meal_count == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	init_mutex(t_info info, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < info.count)
	{
		if (pthread_mutex_init(mutex->fork + i, NULL))
			return (EXIT_FAILURE);
		if (pthread_mutex_init(mutex->meal_time + i, NULL))
			return (EXIT_FAILURE);
		if (pthread_mutex_init(mutex->meal_count + i++, NULL))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&mutex->io, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&mutex->start, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&mutex->stop, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	set_sh_ressource(t_sh *sh)
{
	sh->can_start = false;
	sh->must_stop = false;
	sh->start_time = 0;
}

static int	init_elem(int nb, t_info info, t_mutex *mutex, t_philo *philo)
{
	philo[nb].nb = nb;
	philo[nb].count = info.count;
	philo[nb].eat_time = info.eat_time;
	philo[nb].sleep_time = info.sleep_time;
	philo[nb].starv_time = info.starv_time;
	philo[nb].meal_left = info.meal_left;
	philo[nb].last_meal = 0;
	if (nb == 0)
		philo[nb].left_fork = &mutex->fork[info.count - 1];
	else
		philo[nb].left_fork = mutex->fork + nb - 1;
	philo[nb].right_fork = mutex->fork + nb;
	philo[nb].io = &mutex->io;
	philo[nb].start = &mutex->start;
	philo[nb].stop = &mutex->stop;
	philo[nb].meal_time = mutex->meal_time + nb;
	philo[nb].meal_count = mutex->meal_count + nb;
	return (EXIT_SUCCESS);
}

int	init_philo(t_info info, t_sh *sh, t_philo **philo, t_mutex *mutex)
{
	int	i;

	i = 0;
	ft_bzero(mutex, sizeof(t_mutex));
	*philo = (t_philo *)ft_calloc(info.count, sizeof(t_philo));
	if (*philo == NULL)
		return (EXIT_FAILURE);
	if (malloc_mutex_tab(info, mutex))
		return (EXIT_FAILURE);
	if (init_mutex(info, mutex))
		return (EXIT_FAILURE);
	set_sh_ressource(sh);
	while (i < info.count)
	{
		(*philo)[i].sh = sh;
		if (init_elem(i++, info, mutex, *philo))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
