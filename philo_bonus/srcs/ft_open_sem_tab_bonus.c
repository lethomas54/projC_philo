/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_sem_tab_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:17:16 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 13:54:43 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher_bonus.h"

int	ft_open_sem_tab(t_info info, t_sem_tab *sem_tab)
{
	ft_bzero((void *)sem_tab, sizeof(sem_tab));
	if (sem_unlink("sem_io"))
		if (errno != ENOENT)
			return (EXIT_FAILURE);
	if (sem_unlink("sem_fork"))
		if (errno != ENOENT)
			return (EXIT_FAILURE);
	sem_tab->fork = sem_open("sem_fork", O_CREAT, 777,
			info.nb_philo / 2);
	if (sem_tab->fork == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_tab->io = sem_open("sem_io", O_CREAT, 777, 1);
	if (sem_tab->io == SEM_FAILED)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
