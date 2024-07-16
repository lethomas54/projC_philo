/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 10:29:46 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 19:25:52 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	get_time(time_t *time)
{
	struct timeval	time_struct;

	if (gettimeofday(&time_struct, NULL))
		return (EXIT_FAILURE);
	*time = 1000 * time_struct.tv_sec + time_struct.tv_usec * 0.001;
	return (EXIT_SUCCESS);
}

int	print_locked(char *str, t_philo *philo, t_bool is_reaper)
{
	time_t	time;

	if (pthread_mutex_lock(philo->io))
		return (EXIT_FAILURE);
	if (philo->sh->must_stop == false || is_reaper == true)
	{
		if (get_time(&time)
			|| ft_putnbr_fd((int)(time - philo->sh->start_time), 1)
			|| ft_putstr_fd(" ", 1)
			|| ft_putnbr_fd(philo->nb + 1, 1)
			|| ft_putstr_fd(" ", 1)
			|| ft_putendl_fd(str, 1))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(philo->io))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	philo_usleep(time_t wait_time, t_bool *must_stop, pthread_mutex_t *mutex)
{
	time_t	start;
	time_t	time;
	t_bool	stop;

	stop = false;
	if (get_time(&start))
		return (EXIT_FAILURE);
	time = start;
	while (time - start < wait_time
		&& !get_bool_var(must_stop, &stop, mutex))
	{
		if (usleep(500)
			|| get_time(&time))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
