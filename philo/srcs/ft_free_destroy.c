/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:41:19 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/05 21:30:40 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_free_destroy(int philo_count, t_philo *philo, t_mutex *mutex)
{
	int	return_value;
	int	i;

	return_value = EXIT_SUCCESS;
	i = 0;
	while (i < philo_count)
	{
		if (mutex->fork != NULL)
			if (pthread_mutex_destroy(mutex->fork + i))
				return_value = EXIT_FAILURE;
		if (mutex->meal_upd != NULL)
			if (pthread_mutex_destroy(mutex->meal_upd + i++))
				return_value = EXIT_FAILURE;
	}
	if (pthread_mutex_destroy(&mutex->io))
		return_value = EXIT_FAILURE;
	free(mutex->fork);
	free(mutex->meal_upd);
	free(philo);
	return (return_value);
}
