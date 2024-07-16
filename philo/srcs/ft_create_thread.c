/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:26:29 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 14:46:41 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_thread_join(int philo_count, pthread_t *thread,
	t_bool *must_stop)
{
	int		i;
	int		return_value;
	void	*thread_exit_code;

	i = 0;
	return_value = EXIT_SUCCESS;
	while (i <= philo_count && thread[i] != (pthread_t)0)
	{
		if (pthread_join(thread[i++], &thread_exit_code))
			return_value = EXIT_FAILURE;
		if ((long int)thread_exit_code == EXIT_FAILURE)
		{
			return_value = EXIT_FAILURE;
			*must_stop = true;
		}
		if (i == philo_count)
			*must_stop = true;
	}
	return (return_value);
}

int	ft_create_thread(int philo_count, t_shared *shared, t_philo *philo)
{
	int			i;
	pthread_t	*thread;
	int			return_value;

	i = -1;
	return_value = EXIT_SUCCESS;
	thread = (pthread_t *)ft_calloc(philo_count + 1, sizeof(pthread_t));
	if (thread == NULL)
		return (EXIT_FAILURE);
	while (++i < philo_count && return_value == EXIT_SUCCESS)
		return_value = pthread_create(thread + i, NULL,
				&ft_philo_routine, philo + i) != 0;
	if (return_value == EXIT_SUCCESS)
		return_value = pthread_create(thread + i, NULL,
				&ft_reaper_routine, philo) != 0;
	if (return_value == EXIT_SUCCESS)
		return_value = ft_get_time(&shared->start_time);
	if (return_value == EXIT_FAILURE)
		shared->must_stop = true;
	else
		shared->can_start = true;
	if (ft_thread_join(philo_count, thread, &shared->must_stop))
		return_value = EXIT_FAILURE;
	free(thread);
	return (return_value);
}
