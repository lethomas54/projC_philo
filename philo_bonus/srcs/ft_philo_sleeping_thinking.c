/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_sleeping_thinking.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 03:08:52 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/08 16:08:19 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_philo_sleeping(t_philo *philo)
{
	if (ft_print_locked("is sleeping", philo, true))
		return (EXIT_FAILURE);
	if (ft_philo_usleep(philo->info->time_to_sleep))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_philo_thinking(t_philo *philo)
{
	if (ft_print_locked("is thinking", philo, true))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
