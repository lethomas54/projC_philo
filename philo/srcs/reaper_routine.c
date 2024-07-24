/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:04:31 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/24 14:43:31 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	has_died(t_philo *p, t_bool *must_stop)
{
	time_t	time;

	if (get_time(&time))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(p->m_lm))
		return (EXIT_FAILURE);
	if (time - p->last_meal >= p->starv_time)
	{
		if (set_must_stop(true, p->must_stop, p->m_ms))
			return (EXIT_FAILURE);
		*must_stop = true;
		if (print_locked("has died", p, true))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(p->m_lm))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	is_complete(t_philo *p, int *p_incomp, t_bool *must_stop)
{
	int			meal_left;

	if (pthread_mutex_lock(p->m_ml))
		return (EXIT_FAILURE);
	meal_left = p->meal_left;
	if (pthread_mutex_unlock(p->m_ml))
		return (EXIT_FAILURE);
	if (meal_left == 0)
	{
		(*p_incomp)--;
		if (pthread_mutex_lock(p->m_ml))
			return (EXIT_FAILURE);
		p->meal_left = NO_LIMIT;
		if (pthread_mutex_unlock(p->m_ml))
			return (EXIT_FAILURE);
	}
	if (*p_incomp == 0)
	{
		if (set_must_stop(true, p->must_stop, p->m_ms))
			return (EXIT_FAILURE);
		*must_stop = true;
	}
	return (EXIT_SUCCESS);
}

static int	reaper_simulation(t_philo *p)
{
	int			i;
	t_bool		must_stop;
	int			p_incomp;

	i = 0;
	must_stop = false;
	p_incomp = p->count;
	while (must_stop == false)
	{
		if (has_died(p + i, &must_stop)
			|| is_complete(p + i, &p_incomp, &must_stop)
			|| get_must_stop(p->must_stop, &must_stop, p->m_ms))
			return (EXIT_FAILURE);
		i = (i + 1) % p[i].count;
	}
	return (EXIT_SUCCESS);
}

void	*reaper_routine(void *p_void)
{
	t_philo	*p;
	int		return_value;

	p = (t_philo *)p_void;
	return_value = reaper_simulation(p);
	if (return_value == EXIT_FAILURE)
		set_must_stop(true, p->must_stop, p->m_ms);
	return ((void *)(long int)return_value);
}
