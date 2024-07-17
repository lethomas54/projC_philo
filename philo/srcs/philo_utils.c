/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 10:29:46 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/17 13:30:34 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	get_must_stop(t_bool *to_get, t_bool *getted, pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
		return (EXIT_FAILURE);
	*getted = *to_get;
	if (pthread_mutex_unlock(mutex))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_must_stop(t_bool new_val, t_bool *must_stop,
	pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
		return (EXIT_FAILURE);
	*must_stop = new_val;
	if (pthread_mutex_unlock(mutex))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_time(time_t *time)
{
	struct timeval	time_struct;

	if (gettimeofday(&time_struct, NULL))
		return (EXIT_FAILURE);
	*time = 1000 * time_struct.tv_sec + time_struct.tv_usec * 0.001;
	return (EXIT_SUCCESS);
}

int	print_locked(char *str, t_philo *p, t_bool is_reaper)
{
	time_t	time;

	if (pthread_mutex_lock(p->m_ms))
		return (EXIT_FAILURE);
	if (*p->must_stop == false || is_reaper == true)
	{
		if (get_time(&time)
			|| ft_putnbr_fd((int)(time - p->start_time), 1)
			|| ft_putstr_fd(" ", 1)
			|| ft_putnbr_fd(p->nb + 1, 1)
			|| ft_putstr_fd(" ", 1)
			|| ft_putendl_fd(str, 1))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(p->m_ms))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	philo_usleep(time_t wait_time, t_bool *must_stop, pthread_mutex_t *mutex)
{
	time_t	start;
	time_t	time;
	t_bool	stop;
	int		it;

	it = 0;
	stop = false;
	if (get_time(&start))
		return (EXIT_FAILURE);
	time = start;
	while (time - start < wait_time && stop == false)
	{
		it++;
		if (usleep(500)
			|| get_time(&time))
			return (EXIT_FAILURE);
		if (it == 1000)
		{
			if (get_must_stop(must_stop, &stop, mutex))
				return (EXIT_FAILURE);
			it = 0;
		}
	}
	return (EXIT_SUCCESS);
}
