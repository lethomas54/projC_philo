/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:41:19 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/05 12:28:01 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_end_philo(t_info info, t_mutex_tabs *mutex_tabs)
{
	int	return_value;
	int	i;

	return_value = EXIT_SUCCESS;
	i = 0;
	while (i < info.nb_philo)
	{
		if (pthread_mutex_destroy(mutex_tabs->fork + i))
			return_value = EXIT_FAILURE;
		i++;
	}
	if (pthread_mutex_destroy(&mutex_tabs->io))
		return_value = EXIT_FAILURE;
	if (pthread_mutex_destroy(&mutex_tabs->is_a_philo_dead))
		return_value = EXIT_FAILURE;
	free(mutex_tabs->fork);
	return (return_value);
}
