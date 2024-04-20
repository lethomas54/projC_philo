/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 10:29:46 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/12 18:17:20 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_get_time(time_t *time)
{
	struct timeval	time_struct;

	if (gettimeofday(&time_struct, NULL))
		return (EXIT_FAILURE);
	*time = 1000 * time_struct.tv_sec + time_struct.tv_usec * 0.001;
	return (EXIT_SUCCESS);
}

int	ft_print_locked(char *str, t_philo *philo, t_bool is_reaper)
{
	time_t	time;

	if (pthread_mutex_lock(philo->io))
		return (EXIT_FAILURE);
	if (philo->shared->must_stop == false || is_reaper == true)
	{
		if (ft_get_time(&time))
			return (EXIT_FAILURE);
		if (ft_putnbr_fd((int)(time - philo->shared->start_time), 1))
			return (EXIT_FAILURE);
		if (ft_putstr_fd(" ", 1))
			return (EXIT_FAILURE);
		if (ft_putnbr_fd(philo->nb + 1, 1))
			return (EXIT_FAILURE);
		if (ft_putstr_fd(" ", 1))
			return (EXIT_FAILURE);
		if (ft_putendl_fd(str, 1))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(philo->io))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_philo_usleep(time_t wait_time, t_bool *must_stop)
{
	time_t	time_start;
	time_t	time;

	if (ft_get_time(&time_start))
		return (EXIT_FAILURE);
	time = time_start;
	while (time - time_start < wait_time
		&& *must_stop == false)
	{
		if (usleep(500))
			return (EXIT_FAILURE);
		if (ft_get_time(&time))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
