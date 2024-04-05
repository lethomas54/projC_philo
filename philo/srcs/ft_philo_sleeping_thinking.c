/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_sleeping_thinking.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 03:08:52 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/05 14:42:57 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_philo_sleeping(t_philo_arg *arg, t_bool *is_a_philo_dead)
{
	if (ft_print_locked("is sleeping", arg, is_a_philo_dead))
		return (EXIT_FAILURE);
	if (ft_philo_usleep(arg, arg->info.time_to_sleep, is_a_philo_dead))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_philo_thinking(t_philo_arg *arg, t_bool *is_a_philo_dead)
{
	if (ft_print_locked("is thinking", arg, is_a_philo_dead))
		return (EXIT_FAILURE);
	if (ft_philo_usleep(arg, 50, is_a_philo_dead))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
