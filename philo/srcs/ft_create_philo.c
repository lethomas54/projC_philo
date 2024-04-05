/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:26:29 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/05 12:16:44 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_thread_join(t_info info, pthread_t *thread_tab)
{
	int	return_value;

	return_value = EXIT_SUCCESS;
	while (info.nb_philo--)
		if (pthread_join(thread_tab[info.nb_philo], NULL))
			return_value = EXIT_FAILURE;
	free(thread_tab);
	return (return_value);
}

static void	ft_free_thread_arg(t_philo_arg *philo_thread_arg)
{
	free(philo_thread_arg->time_last_meal);
	free(philo_thread_arg);
}

static int	ft_set_share_resources(t_info info, t_bool **fork_available,
	t_bool *is_a_philo_dead)
{
	*fork_available = (t_bool *)malloc(sizeof(t_bool) * info.nb_philo);
	if (*fork_available == NULL)
		return (EXIT_FAILURE);
	while (info.nb_philo--)
		(*fork_available)[info.nb_philo] = true;
	*is_a_philo_dead = false;
	return (EXIT_SUCCESS);
}

static t_philo_arg	*ft_set_philo_arg(t_info info, t_mutex_tabs *mutex_tabs,
	t_bool *is_a_philo_dead, t_bool *fork_available)
{
	t_philo_arg	*thread_arg;
	time_t		*time_last_meal;

	thread_arg = (t_philo_arg *)ft_calloc(1, sizeof(t_philo_arg));
	if (thread_arg == NULL)
		return (NULL);
	time_last_meal = (time_t *)malloc(sizeof(time_t));
	if (time_last_meal == NULL)
		return (free(thread_arg), NULL);
	*time_last_meal = info.init_time;
	thread_arg->time_last_meal = time_last_meal;
	thread_arg->fork_available = fork_available;
	thread_arg->info = info;
	thread_arg->mutex_tabs = mutex_tabs;
	thread_arg->is_a_philo_dead = is_a_philo_dead;
	return (thread_arg);
}

int	ft_create_philo(t_info info, pthread_t *thread_tab,
	t_mutex_tabs *mutex_tabs)
{
	int			nb_thread;
	t_bool		is_a_philo_dead;
	t_bool		*fork_available;
	t_philo_arg	*philo_thread_arg;

	nb_thread = 0;
	if (ft_set_share_resources(info, &fork_available, &is_a_philo_dead))
		return (EXIT_FAILURE);
	while (nb_thread < info.nb_philo)
	{
		philo_thread_arg = ft_set_philo_arg(info, mutex_tabs, &is_a_philo_dead,
				fork_available);
		if (philo_thread_arg == NULL)
			return (EXIT_FAILURE);
		philo_thread_arg->nb_thread = nb_thread;
		if (pthread_create(thread_tab + nb_thread, NULL, &ft_philo,
				(void *)philo_thread_arg))
			return (ft_free_thread_arg(philo_thread_arg), EXIT_FAILURE);
		nb_thread++;
	}
	if (ft_thread_join(info, thread_tab))
		return (EXIT_FAILURE);
	free(fork_available);
	return (EXIT_SUCCESS);
}
