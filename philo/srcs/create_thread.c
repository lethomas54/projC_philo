/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:26:29 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/24 14:38:00 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	thread_join(int count, pthread_t *thread)
{
	int		i;
	void	*thread_exit_code;
	int		return_value;

	i = 0;
	while (i <= count)
	{
		if (pthread_join(thread[i++], &thread_exit_code))
			return (EXIT_FAILURE);
		if (thread_exit_code == (void *)EXIT_FAILURE)
			return_value = EXIT_FAILURE;
	}
	return (return_value);
}

static int	launch_thread(int count, t_philo *p, pthread_t *thread)
{
	int	i;

	i = -1;
	while (++i < count)
		if (pthread_create(thread + i, NULL, &philo_routine, p + i))
			return (EXIT_FAILURE);
	if (pthread_create(thread + i, NULL, &reaper_routine, p))
		return (EXIT_FAILURE);
	if (thread_join(count, thread))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_thread(int count, t_philo *p)
{
	pthread_t	*thread;
	int			return_value;

	thread = (pthread_t *)malloc(count + 1 * sizeof(pthread_t));
	if (thread == NULL)
		return (EXIT_FAILURE);
	return_value = launch_thread(count, p, thread);
	free(thread);
	return (return_value);
}
