/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:26:29 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 19:17:28 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	thread_join(int count, pthread_t *thread,
	t_bool *must_stop, pthread_mutex_t *stop_mutex)
{
	int		i;
	void	*thread_exit_code;

	i = 0;
	while (i <= count)
	{
		if (pthread_join(thread[i++], &thread_exit_code))
			return (EXIT_FAILURE);
		if ((long int)thread_exit_code == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (i == count)
			if (set_must_stop(true, must_stop, stop_mutex))
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	create_thread(int count, t_sh *sh, t_philo *philo)
{
	int			i;
	pthread_t	*thread;

	i = -1;
	thread = (pthread_t *)ft_calloc(count + 1, sizeof(pthread_t));
	if (thread == NULL)
		return (EXIT_FAILURE);
	while (++i < count)
		if (pthread_create(thread + i, NULL, &philo_routine, philo + i))
			return (EXIT_FAILURE);
	if (pthread_create(thread + i, NULL, &reaper_routine, philo))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(philo->start))
		return (EXIT_FAILURE);
	sh->can_start = true;
	if (pthread_mutex_unlock(philo->start))
		return (EXIT_FAILURE);
	if (thread_join(count, thread, &sh->must_stop, philo->stop))
		return (EXIT_FAILURE);
	free(thread);
	return (EXIT_SUCCESS);
}
