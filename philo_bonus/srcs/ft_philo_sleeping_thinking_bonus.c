/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_sleeping_thinking_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 03:08:52 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 13:54:43 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher_bonus.h"

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
