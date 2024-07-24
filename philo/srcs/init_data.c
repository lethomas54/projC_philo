/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:17:16 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/24 14:21:11 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	malloc_mutex_tab(t_info info, t_mutex *mutex)
{
	mutex->fork = (pthread_mutex_t *)ft_calloc(info.count,
			sizeof(pthread_mutex_t));
	if (mutex->fork == NULL)
		return (EXIT_FAILURE);
	mutex->last_meal = (pthread_mutex_t *)ft_calloc(info.count,
			sizeof(pthread_mutex_t));
	if (mutex->last_meal == NULL)
		return (EXIT_FAILURE);
	mutex->meal_left = (pthread_mutex_t *)ft_calloc(info.count,
			sizeof(pthread_mutex_t));
	if (mutex->meal_left == NULL)
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
		if (pthread_mutex_init(mutex->last_meal + i, NULL))
			return (EXIT_FAILURE);
		if (pthread_mutex_init(mutex->meal_left + i++, NULL))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&mutex->must_stop, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	init_elem(int nb, t_info info, t_mutex *mutex, t_philo *p)
{
	p[nb].nb = nb;
	p[nb].count = info.count;
	p[nb].eat_time = (time_t)info.eat_time;
	p[nb].sleep_time = (time_t)info.sleep_time;
	p[nb].starv_time = (time_t)info.starv_time;
	p[nb].meal_left = info.meal_left;
	if (nb == 0)
		p[nb].left_fork = &mutex->fork[info.count - 1];
	else
		p[nb].left_fork = mutex->fork + nb - 1;
	p[nb].right_fork = mutex->fork + nb;
	p[nb].m_ms = &mutex->must_stop;
	p[nb].m_lm = mutex->last_meal + nb;
	p[nb].m_ml = mutex->meal_left + nb;
}

int	init_data(t_info info, t_bool *must_stop, t_philo **p, t_mutex *mutex)
{
	int		i;
	time_t	time;

	i = 0;
	*must_stop = false;
	ft_bzero(mutex, sizeof(t_mutex));
	*p = (t_philo *)malloc(info.count * sizeof(t_philo));
	if (*p == NULL)
		return (EXIT_FAILURE);
	if (malloc_mutex_tab(info, mutex)
		|| init_mutex(info, mutex))
		return (EXIT_FAILURE);
	if (get_time(&time))
		return (EXIT_FAILURE);
	while (i < info.count)
	{
		(*p)[i].must_stop = must_stop;
		(*p)[i].start_time = time;
		(*p)[i].last_meal = time;
		init_elem(i++, info, mutex, *p);
	}
	return (EXIT_SUCCESS);
}
