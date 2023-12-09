/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:26:29 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/07 12:04:52 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_thread_join(t_info info, pthread_t **thread_tab)
{
	int	return_value;

	if (*thread_tab == NULL)
		return (EXIT_SUCCESS);
	return_value = EXIT_SUCCESS;
	while (info.nb_philo--)
		if (pthread_join((*thread_tab)[info.nb_philo], NULL))
			return_value = EXIT_FAILURE;
	free(*thread_tab);
	*thread_tab = NULL;
	return (return_value);
}

static void	ft_free_thread_arg(t_philo_arg **philo_thread_arg)
{
	if (*philo_thread_arg == NULL)
		return ;
	free((*philo_thread_arg)->time_last_meal);
	free(*philo_thread_arg);
	*philo_thread_arg = NULL;
}

static int	ft_set_share_resources(t_info info,
	t_bool **fork_available, t_bool **is_a_philo_dead)
{
	*fork_available = (t_bool *)malloc(sizeof(t_bool) * info.nb_philo);
	if (*fork_available == NULL)
		return (EXIT_FAILURE);
	while (info.nb_philo--)
		(*fork_available)[info.nb_philo] = true;
	*is_a_philo_dead = (t_bool *)malloc(sizeof(t_bool));
	if (*is_a_philo_dead == NULL)
		return (free(fork_available), EXIT_FAILURE);
	**is_a_philo_dead = false;
	return (EXIT_SUCCESS);
}

static t_philo_arg	*ft_set_philo_arg(t_info *info,
	t_mutex_tabs *mutex_tabs, t_bool *is_a_philo_dead, t_bool *fork_available)
{
	t_philo_arg	*thread_arg;
	time_t		*time_last_meal;

	thread_arg = (t_philo_arg *)ft_calloc(1, sizeof(t_philo_arg));
	if (thread_arg == NULL)
		return (NULL);
	time_last_meal = (time_t *)malloc(sizeof(time_t));
	if (time_last_meal == NULL)
		return (free(thread_arg), NULL);
	*time_last_meal = info->init_time;
	thread_arg->time_last_meal = time_last_meal;
	thread_arg->fork_available = fork_available;
	thread_arg->info = info;
	thread_arg->mutex_tabs = mutex_tabs;
	thread_arg->is_a_philo_dead = is_a_philo_dead;
	return (thread_arg);
}

int	ft_create_philo(t_info *info, pthread_t **thread_tab,
	t_mutex_tabs *mutex_tabs)
{
	int			nb_thread;
	t_bool		*is_a_philo_dead;
	t_bool		*fork_available;
	t_philo_arg	*philo_thread_arg;

	nb_thread = 0;
	if (ft_set_share_resources(*info, &fork_available, &is_a_philo_dead))
		return (EXIT_FAILURE);
	while (nb_thread < info->nb_philo)
	{
		philo_thread_arg = ft_set_philo_arg(info, mutex_tabs, is_a_philo_dead,
				fork_available);
		philo_thread_arg->nb_thread = nb_thread;
		if (philo_thread_arg == NULL)
			return (EXIT_FAILURE);
		if (pthread_create(*thread_tab + nb_thread, NULL, &ft_philo,
				(void *)philo_thread_arg))
			return (ft_free_thread_arg(&philo_thread_arg), EXIT_FAILURE);
		nb_thread++;
	}
	if (ft_thread_join(*info, thread_tab))
		return (EXIT_FAILURE);
	free(is_a_philo_dead);
	free(fork_available);
	return (EXIT_SUCCESS);
}
//verfier le cas de sortie avec erreur
