/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:41:19 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/30 11:54:58 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	destroy(int count, t_mutex *mutex)
{
	int	i;
	int	return_value;

	i = 0;
	return_value = EXIT_SUCCESS;
	while (i < count)
	{
		if (mutex->fork != NULL)
			if (pthread_mutex_destroy(mutex->fork + i))
				return_value = EXIT_FAILURE;
		if (mutex->last_meal != NULL)
			if (pthread_mutex_destroy(mutex->last_meal + i))
				return_value = EXIT_FAILURE;
		if (mutex->meal_left != NULL)
			if (pthread_mutex_destroy(mutex->meal_left + i))
				return_value = EXIT_FAILURE;
		i++;
	}
	if (pthread_mutex_destroy(&mutex->must_stop))
		return_value = EXIT_FAILURE;
	return (EXIT_SUCCESS);
}

int	free_destroy(int count, t_philo *philo, t_mutex *mutex)
{
	int	return_value;

	return_value = EXIT_SUCCESS;
	if (destroy(count, mutex))
		return_value = EXIT_FAILURE;
	free(mutex->fork);
	free(mutex->last_meal);
	free(mutex->meal_left);
	free(philo);
	return (return_value);
}
