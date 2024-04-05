/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_sem_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:41:19 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/05 15:06:03 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_close_sem_tab(t_sem_tab *sem_tab, t_bool is_main_process)
{
	int	return_value;

	return_value = EXIT_SUCCESS;
	if (sem_tab->fork_first != NULL && sem_tab->fork_first != SEM_FAILED)
		if (sem_close(sem_tab->fork_first))
			return_value = EXIT_FAILURE;
	if (sem_tab->fork_scnd != NULL && sem_tab->fork_scnd != SEM_FAILED)
		if (sem_close(sem_tab->fork_scnd))
			return_value = EXIT_FAILURE;
	if (sem_tab->io != NULL && sem_tab->io != SEM_FAILED)
		if (sem_close(sem_tab->io))
			return_value = EXIT_FAILURE;
	if (is_main_process == true)
	{
		if (sem_unlink("sem_io"))
			if (errno != ENOENT)
				return_value = EXIT_FAILURE;
		if (sem_unlink("sem_fork_first"))
			if (errno != ENOENT)
				return_value = EXIT_FAILURE;
		if (sem_unlink("sem_fork_scnd"))
			if (errno != ENOENT)
				return_value = EXIT_FAILURE;
	}
	return (return_value);
}
