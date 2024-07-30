/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_for_children_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:27:33 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 13:54:43 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher_bonus.h"

static t_bool	ft_children_not_done(t_info info, pid_t *child_pid)
{
	while (info.nb_philo--)
		if (!(child_pid[info.nb_philo] == 0 || child_pid[info.nb_philo] == -1))
			return (true);
	return (false);
}

static void	ft_delete_entry(t_info info, pid_t *child_pid,
	pid_t child_pid_return)
{
	while (info.nb_philo--)
		if (child_pid[info.nb_philo] == child_pid_return)
			child_pid[info.nb_philo] = 0;
}

static int	ft_kill(t_info info, pid_t *child_pid)
{
	while (info.nb_philo--)
		if (!(child_pid[info.nb_philo] == 0 || child_pid[info.nb_philo] == -1))
			if (kill(child_pid[info.nb_philo], SIGINT))
				return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_check_child_status(t_info info, int status, pid_t *child_pid,
	int *return_value)
{
	if (WIFEXITED(status) == false)
		return (EXIT_SUCCESS);
	if (WEXITSTATUS(status) == EXIT_FAILURE)
	{
		*return_value = EXIT_FAILURE;
		return (EXIT_SUCCESS);
	}
	if (WEXITSTATUS(status) == PHILO_DEAD)
		if (ft_kill(info, child_pid))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_wait_for_children(t_info info, pid_t **child_pid,
	int global_return_value)
{
	int		return_value;
	int		status;
	pid_t	child_pid_return;

	return_value = EXIT_SUCCESS;
	if (*child_pid == NULL)
		return (EXIT_FAILURE);
	if (global_return_value == EXIT_FAILURE)
		if (ft_kill(info, *child_pid))
			return (EXIT_FAILURE);
	while (ft_children_not_done(info, *child_pid))
	{
		child_pid_return = waitpid(0, &status, WNOHANG);
		if (child_pid_return == -1)
			return (ft_free((void **)child_pid), EXIT_FAILURE);
		else if (child_pid_return == 0)
			continue ;
		ft_delete_entry(info, *child_pid, child_pid_return);
		if (ft_check_child_status(info, status, *child_pid, &return_value))
			return (ft_free((void **)child_pid), EXIT_FAILURE);
	}
	ft_free((void **)child_pid);
	return (return_value);
}
