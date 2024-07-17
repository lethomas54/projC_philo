/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:32:58 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/17 12:25:40 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	set_meal_left(int *meal_left, pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
		return (EXIT_FAILURE);
	*meal_left -= (*meal_left != NO_LIMIT);
	if (pthread_mutex_unlock(mutex))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	set_last_meal(time_t *last_meal, pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
		return (EXIT_FAILURE);
	if (get_time(last_meal))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(mutex))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	eating(t_philo *p)
{
	if (pthread_mutex_lock(p->left_fork)
		|| print_locked("has taken a fork", p, false)
		|| pthread_mutex_lock(p->right_fork)
		|| print_locked("has taken a fork", p, false)
		|| set_last_meal(&p->last_meal, p->m_lm)
		|| print_locked("is eating", p, false)
		|| philo_usleep(p->eat_time, p->must_stop, p->m_ms)
		|| pthread_mutex_unlock(p->left_fork)
		|| pthread_mutex_unlock(p->right_fork)
		|| set_meal_left(&p->meal_left, p->m_ml))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	sleep_think(t_philo *p)
{
	if (print_locked("is sleeping", p, false)
		|| philo_usleep(p->sleep_time, p->must_stop, p->m_ms)
		|| print_locked("is thinking", p, false))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *p_void)
{
	t_philo	*p;
	t_bool	must_stop;

	p = (t_philo *)p_void;
	must_stop = false;
	if (p->count == 1)
	{
		if (print_locked("has taken a fork", p, false))
			return ((void *)EXIT_FAILURE);
		return ((void *)EXIT_SUCCESS);
	}
	if (p->nb % 2 != 0)
		if (philo_usleep(p->eat_time * 0.5, p->must_stop, p->m_ms))
			return ((void *)EXIT_FAILURE);
	while (must_stop == false)
	{
		if (eating(p)
			|| sleep_think(p)
			|| get_must_stop(p->must_stop, &must_stop, p->m_ms))
			return ((void *)EXIT_FAILURE);
	}
	return ((void *)EXIT_SUCCESS);
}
