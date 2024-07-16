/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:32:58 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 19:25:27 by lethomas         ###   ########.fr       */
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

static int	set_meal_time(time_t *meal_time, pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
		return (EXIT_FAILURE);
	if (get_time(meal_time))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(mutex))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_must_stop(t_bool new_val, t_bool *must_stop,
	pthread_mutex_t *stop_mutex)
{
	if (pthread_mutex_lock(stop_mutex))
		return (EXIT_FAILURE);
	*must_stop = new_val;
	if (pthread_mutex_unlock(stop_mutex))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_bool_var(t_bool *to_get, t_bool *getted, pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
		return (EXIT_FAILURE);
	*getted = *to_get;
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
		|| pthread_mutex_lock(p->meal_time)
		|| set_meal_time(&p->last_meal, p->meal_time)
		|| pthread_mutex_unlock(p->meal_time)
		|| print_locked("is eating", p, false)
		|| philo_usleep(p->eat_time, &p->sh->must_stop, p->stop)
		|| pthread_mutex_unlock(p->left_fork)
		|| pthread_mutex_unlock(p->right_fork)
		|| set_meal_left(&p->meal_left, p->meal_count))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	sleep_think(t_philo *p)
{
	if (print_locked("is sleeping", p, false)
		|| philo_usleep(p->sleep_time, &p->sh->must_stop, p->stop)
		|| print_locked("is thinking", p, false))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *p_void)
{
	t_philo	*p;
	t_bool	start;
	t_bool	stop;
	
	p = (t_philo *)p_void;
	start = false;
	stop = false;
	while (start == false)
		if (get_bool_var(&p->sh->can_start, &start, p->start))
			return ((void *)EXIT_FAILURE);
	if (set_meal_time(&p->last_meal, p->meal_time))
		return ((void *)EXIT_FAILURE);
	if (p->nb % 2 != 0)
		if (philo_usleep(p->eat_time * 0.5, &p->sh->must_stop, p->stop))
			return ((void *)EXIT_FAILURE);
	while (!get_bool_var(&p->sh->must_stop, &stop, p->stop))
	{
		if (p->count == 1)
			continue ;
		if (eating(p)
			|| sleep_think(p))
			return ((void *)EXIT_FAILURE);
	}
	return ((void *)EXIT_SUCCESS);
}

static int	has_died(t_philo *philo)
{
	time_t	time;

	if (get_time(&time))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(philo->meal_time))
		return (EXIT_FAILURE);
	if ((int)time - philo->last_meal >= philo->starv_time)
	{
		if (set_must_stop(true, &philo->sh->must_stop, philo->stop))
			return (EXIT_FAILURE);
		if (print_locked("has died", philo, true))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(philo->meal_time))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*reaper_routine(void *philo_void)
{
	int			i;
	t_philo		*philo;
	t_bool		must_stop;
	t_bool		can_start;

	i = 0;
	philo = (t_philo *)philo_void;
	can_start = false;
	must_stop = false;
	while (can_start == false)
		if (get_bool_var(&philo->sh->can_start, &can_start,
				philo->start))
			return ((void *)EXIT_FAILURE);
	while (get_bool_var(&philo->sh->must_stop,
			&must_stop, philo->stop) == false)
	{
		if (philo[i].meal_left != 0) //to mutex
			if (has_died(philo + i))
				return ((void *)EXIT_FAILURE);
		i = (i + 1) % philo[i].count;
	}
	return ((void *)EXIT_SUCCESS);
}
