/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:02:39 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/30 12:18:37 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher_bonus.h"

static int	ft_philo_program(int argc, char **argv)
{
	pid_t		*child_pid;
	t_bool		is_main_process;
	t_info		info;
	t_sem_tab	sem_tab;
	int			return_value;

	is_main_process = true;
	return_value = EXIT_SUCCESS;
	if (ft_set_info(argc, argv, &info))
	{
		ft_putendl_fd("Invalid arguments.", 2);
		return (EXIT_FAILURE);
	}
	if (ft_open_sem_tab(info, &sem_tab)
		|| ft_create_children(info, &sem_tab, &child_pid, &is_main_process))
		return_value = EXIT_FAILURE;
	if (is_main_process == true)
		if (ft_wait_for_children(info, &child_pid, return_value))
			return_value = EXIT_FAILURE;
	if (ft_close_sem_tab(&sem_tab, is_main_process))
		return_value = EXIT_FAILURE;
	return (return_value);
}

int	main(int argc, char **argv)
{
	errno = 0;
	if (ft_philo_program(argc, argv))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
