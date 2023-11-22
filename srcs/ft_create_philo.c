/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:26:29 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/22 01:42:42 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static t_philo_thread_arg	*ft_set_philo_arg(t_philo_info philo_info,
	t_mutex_tabs *mutex_tabs, int nb_thread, t_bool *is_a_philo_dead, t_bool *fork_available)
{
	t_philo_thread_arg	*thread_arg;
	t_philo_info		*philo_info_cpy;
	time_t				*time_last_meal;

	thread_arg = (t_philo_thread_arg *)malloc(sizeof(t_philo_thread_arg));
	if (thread_arg == NULL)
		return (NULL);
	ft_bzero((void *)thread_arg, sizeof(t_philo_thread_arg));
	philo_info_cpy = (t_philo_info *)malloc(sizeof(t_philo_info));
	if (philo_info_cpy == NULL)
		return (free(thread_arg), NULL);
	time_last_meal = (time_t *)malloc(sizeof(time_t));
	if (time_last_meal == NULL)
		return (free(thread_arg), free(philo_info_cpy), NULL);
	if (ft_update_last_meal_time(nb_thread, mutex_tabs,
		time_last_meal))
		return (free(thread_arg), free(philo_info_cpy), free(time_last_meal), NULL);
	*philo_info_cpy = philo_info;
	thread_arg->fork_available = fork_available;
	thread_arg->philo_info = philo_info_cpy;
	thread_arg->nb_thread = nb_thread;
	thread_arg->mutex_tabs = mutex_tabs;
	thread_arg->is_a_philo_dead = is_a_philo_dead;
	thread_arg->time_last_meal = time_last_meal;
	return (thread_arg);
}

static t_death_thread_arg	*ft_set_death_arg(t_philo_info philo_info,
	t_mutex_tabs *mutex_tabs, t_philo_thread_arg *philo_thread_arg,
	t_death_thread_arg *death_thread_arg)
{
	if (death_thread_arg == NULL)
	{
		death_thread_arg = (t_death_thread_arg *)malloc(sizeof(t_death_thread_arg));
		if (death_thread_arg == NULL)
			return (NULL);
		ft_bzero((void *)death_thread_arg, sizeof(t_death_thread_arg));
		death_thread_arg->time_last_meal = (time_t **)malloc(sizeof(time_t *)
			* philo_info.nb_philo);
		if (death_thread_arg->time_last_meal == NULL)
			return (free(death_thread_arg), NULL);
		death_thread_arg->nb_must_eat = (int **)malloc(sizeof(int *)
			* philo_info.nb_philo);
		if (death_thread_arg->nb_must_eat == NULL)
			return (free(death_thread_arg->time_last_meal), free(death_thread_arg), NULL);
		death_thread_arg->philo_info = philo_info;
		death_thread_arg->mutex_tabs = mutex_tabs;
		death_thread_arg->is_a_philo_dead = philo_thread_arg->is_a_philo_dead;
	}
	death_thread_arg->time_last_meal[philo_thread_arg->nb_thread]
		= philo_thread_arg->time_last_meal;
	death_thread_arg->nb_must_eat[philo_thread_arg->nb_thread]
		= &philo_thread_arg->philo_info->nb_must_eat;
	return (death_thread_arg);
}

static void	ft_free_thread_arg(t_philo_thread_arg **philo_thread_arg)
{
	if (philo_thread_arg == NULL)
		return ;
	free((*philo_thread_arg)->time_last_meal);
	free((*philo_thread_arg)->philo_info);
	free (*philo_thread_arg);
	*philo_thread_arg = NULL; 
}

int	ft_create_philo(t_philo_info philo_info, pthread_t **thread_tab, 
	t_mutex_tabs *mutex_tabs)
{
	t_philo_thread_arg	*philo_thread_arg;
	int					nb_thread;
	t_bool				is_a_philo_dead;
	t_bool				*fork_available;

	philo_thread_arg = NULL;
	nb_thread = 0;
	is_a_philo_dead = false;
	fork_available = (t_bool *)malloc(sizeof(t_bool) * philo_info.nb_philo);
	if (fork_available == NULL)
		return (EXIT_FAILURE);
	int	i = 0;
	while (i < philo_info.nb_philo)
		fork_available[i++] = true;
	while (nb_thread < philo_info.nb_philo)
	{
		philo_thread_arg = ft_set_philo_arg(philo_info, mutex_tabs, nb_thread, &is_a_philo_dead, fork_available);
		if (philo_thread_arg == NULL)
			return (ft_free_thread_arg(&philo_thread_arg), EXIT_FAILURE);
		if (philo_thread_arg == NULL)
			return (ft_free_thread_arg(&philo_thread_arg), EXIT_FAILURE);
		if (pthread_create(*thread_tab + nb_thread, NULL, &ft_philo, (void *)philo_thread_arg))
			return (ft_free_thread_arg(&philo_thread_arg), EXIT_FAILURE);
		nb_thread++;
	}
	return (EXIT_SUCCESS);
}
