/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 10:29:46 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/15 17:35:18 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_print_locked(char *str, t_philo *philo, t_bool do_sem_post)
{
	time_t	time;

	if (sem_wait(philo->sem_tab->io))
		return (EXIT_FAILURE);
	if (ft_get_time(&time))
		return (EXIT_FAILURE);
	if (printf("%d %d %s\n", (int)(time - philo->info->init_time),
		philo->nb_process + 1, str) == -1)
		return (EXIT_FAILURE);
	if (do_sem_post == true)
		if (sem_post(philo->sem_tab->io))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_philo_usleep(time_t time_to_sleep)
{
	time_t	time_start;
	time_t	time;

	if (ft_get_time(&time_start))
		return (EXIT_FAILURE);
	time = time_start;
	while (time - time_start < time_to_sleep)
	{
		if (usleep(500))
			return (EXIT_FAILURE);
		if (ft_get_time(&time))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
