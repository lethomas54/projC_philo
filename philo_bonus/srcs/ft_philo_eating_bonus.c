/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_eating_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:41:37 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 15:26:59 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher_bonus.h"

static int	ft_philo_get_forks(t_philo *philo)
{
	if (sem_wait(philo->sem_tab->fork))
		return (EXIT_FAILURE);
	if (ft_print_locked("has taken a fork", philo, true))
		return (EXIT_FAILURE);
	if (ft_print_locked("has taken a fork", philo, true))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_philo_let_forks(t_philo *philo)
{
	if (sem_post(philo->sem_tab->fork))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_update_last_meal_time(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->mutex_death))
		return (EXIT_FAILURE);
	if (ft_get_time(&philo->last_meal_time))
		return (EXIT_FAILURE);
	philo->nb_meal_left -= (philo->nb_meal_left != NO_LIMIT);
	if (pthread_mutex_unlock(&philo->mutex_death))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_philo_eating(t_philo *philo)
{
	if (ft_philo_get_forks(philo))
		return (EXIT_FAILURE);
	if (ft_update_last_meal_time(philo))
		return (EXIT_FAILURE);
	if (ft_print_locked("is eating", philo, true))
		return (EXIT_FAILURE);
	if (ft_philo_usleep(philo->info->time_to_eat))
		return (EXIT_FAILURE);
	if (ft_philo_let_forks(philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
