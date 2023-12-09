/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_children.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:26:29 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/09 00:44:57 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_set_philo(t_info *info, t_sem_tab *sem_tab, int nb_process,
	t_philo	*philo)
{
	philo->nb_process = nb_process;
	philo->last_meal_time = info->init_time;
	philo->info = info;
	philo->sem_tab = sem_tab;
	philo->nb_meal_left = info->nb_must_eat;
	if (pthread_mutex_init(&philo->mutex_death, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_create_children(t_info info, t_sem_tab *sem_tab, pid_t **child_pid,
	t_bool *is_main_process)
{
	int		nb_process;
	t_philo	philo;

	nb_process = 0;
	*child_pid = (pid_t *)ft_calloc(info.nb_philo, sizeof(pid_t));
	if (*child_pid == NULL)
		return (EXIT_FAILURE);
	while (nb_process < info.nb_philo)
	{
		(*child_pid)[nb_process] = fork();
		if ((*child_pid)[nb_process] < 0)
			return (ft_free((void **)child_pid), EXIT_FAILURE);
		if ((*child_pid)[nb_process] == 0)
		{
			*is_main_process = false;
			ft_free((void **)child_pid);
			if (ft_set_philo(&info, sem_tab, nb_process, &philo))
				return (EXIT_FAILURE);
			if (ft_philo(&philo))
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		nb_process++;
	}
	return (EXIT_SUCCESS);
}
