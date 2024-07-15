/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_sem_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:41:19 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/15 16:57:35 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_close_sem_tab(t_sem_tab *sem_tab, t_bool is_main_process)
{
	int	return_value;

	return_value = EXIT_SUCCESS;
	if (sem_tab->fork != NULL && sem_tab->fork != SEM_FAILED)
		if (sem_close(sem_tab->fork))
			return_value = EXIT_FAILURE;
	if (sem_tab->io != NULL && sem_tab->io != SEM_FAILED)
		if (sem_close(sem_tab->io))
			return_value = EXIT_FAILURE;
	if (is_main_process == true)
	{
		if (sem_unlink("sem_io"))
			if (errno != ENOENT)
				return_value = EXIT_FAILURE;
		if (sem_unlink("sem_fork"))
			if (errno != ENOENT)
				return_value = EXIT_FAILURE;
	}
	return (return_value);
}
