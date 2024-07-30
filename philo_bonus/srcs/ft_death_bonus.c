/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 22:52:21 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 13:54:43 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher_bonus.h"

static int	ft_is_philo_dead(t_philo *philo, t_bool *is_philo_dead)
{
	time_t	time;

	if (ft_get_time(&time))
		return (EXIT_FAILURE);
	if (time - philo->last_meal_time >= philo->info->time_to_die)
		*is_philo_dead = true;
	if (*is_philo_dead == true)
		if (printf("%d %d %s\n", (int)(time - philo->info->init_time),
			philo->nb_process + 1, "has died") == -1)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_look_for_death(t_philo *philo, t_bool *is_philo_dead,
	int	*nb_must_eat)
{
	if (sem_wait(philo->sem_tab->io))
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(&philo->mutex_death))
		return (EXIT_FAILURE);
	*nb_must_eat = philo->nb_meal_left;
	if (*nb_must_eat != 0
		&& ft_is_philo_dead(philo, is_philo_dead))
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(&philo->mutex_death))
		return (EXIT_FAILURE);
	if (*is_philo_dead == false)
	{
		if (sem_post(philo->sem_tab->io))
			return (EXIT_FAILURE);
	}
	else
		return (PHILO_DEAD);
	return (EXIT_SUCCESS);
}

void	*ft_death(void *philo)
{
	t_bool	is_philo_dead;
	int		*return_value;

	return_value = (int *)ft_calloc(1, sizeof(int));
	if (return_value == NULL)
		return (NULL);
	*return_value = EXIT_SUCCESS;
	is_philo_dead = false;
	while (((t_philo *)philo)->nb_meal_left != 0)
	{
		*return_value = ft_look_for_death((t_philo *)philo, &is_philo_dead,
				&((t_philo *)philo)->nb_meal_left);
		if (*return_value != EXIT_SUCCESS)
			exit(*return_value);
	}
	return ((void *)return_value);
}
