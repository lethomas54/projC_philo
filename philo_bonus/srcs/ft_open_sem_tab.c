/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_sem_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:17:16 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/09 00:08:15 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_open_sem_tab(t_info info, t_sem_tab *sem_tab)
{
	ft_bzero((void *)sem_tab, sizeof(sem_tab));
	if (sem_unlink("sem_io"))
		if (errno != ENOENT)
			return (EXIT_FAILURE);
	if (sem_unlink("sem_fork_first"))
		if (errno != ENOENT)
			return (EXIT_FAILURE);
	if (sem_unlink("sem_fork_scnd"))
		if (errno != ENOENT)
			return (EXIT_FAILURE);
	sem_tab->fork_first = sem_open("sem_fork_first", O_CREAT, 777,
			info.nb_philo - info.nb_philo / 2);
	if (sem_tab->fork_first == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_tab->fork_scnd = sem_open("sem_fork_scnd", O_CREAT, 777,
			info.nb_philo / 2);
	if (sem_tab->fork_scnd == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_tab->io = sem_open("sem_io", O_CREAT, 777, 1);
	if (sem_tab->io == SEM_FAILED)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
