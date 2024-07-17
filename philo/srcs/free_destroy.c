/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:41:19 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/17 11:37:07 by lethomas         ###   ########.fr       */
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
		if (pthread_mutex_destroy(mutex->last_meal + i))
			return (EXIT_FAILURE);
		if (pthread_mutex_destroy(mutex->meal_left + i++))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_destroy(&mutex->must_stop))
		return (EXIT_FAILURE);
	free(mutex->fork);
	free(mutex->last_meal);
	free(mutex->meal_left);
	free(philo);
	return (EXIT_SUCCESS);
}
