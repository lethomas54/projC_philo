/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:41:19 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 19:12:09 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	free_destroy(int count, t_philo *philo, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_destroy(mutex->fork + i))
			return (EXIT_FAILURE);
		if (pthread_mutex_destroy(mutex->meal_time + i))
			return (EXIT_FAILURE);
		if (pthread_mutex_destroy(mutex->meal_count + i++))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_destroy(&mutex->io))
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&mutex->stop))
		return (EXIT_FAILURE);
	if (pthread_mutex_destroy(&mutex->start))
		return (EXIT_FAILURE);
	free(mutex->fork);
	free(mutex->meal_time);
	free(mutex->meal_count);
	free(philo);
	return (EXIT_SUCCESS);
}
