/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:26:29 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/17 13:38:33 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	thread_join(int count, pthread_t *thread)
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
	}
	return (EXIT_SUCCESS);
}

int	create_thread(int count, t_philo *p)
{
	int			i;
	pthread_t	*thread;

	i = -1;
	thread = (pthread_t *)malloc(count + 1 * sizeof(pthread_t));
	if (thread == NULL)
		return (EXIT_FAILURE);
	while (++i < count)
		if (pthread_create(thread + i, NULL, &philo_routine, p + i))
			return (EXIT_FAILURE);
	if (pthread_create(thread + i, NULL, &reaper_routine, p))
		return (EXIT_FAILURE);
	if (thread_join(count, thread))
		return (EXIT_FAILURE);
	free(thread);
	return (EXIT_SUCCESS);
}
