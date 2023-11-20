/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:41:19 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/20 16:00:24 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_create_tabs(t_philo_info philo_info, pthread_t **thread_tab,
	t_mutex_tabs **mutex_tabs)
{
	*thread_tab = NULL;
	*mutex_tabs = NULL;
	*thread_tab = (pthread_t *)malloc(sizeof(pthread_t)
		* (philo_info.nb_philo + 1));
	if (*thread_tab == NULL)
		return (EXIT_FAILURE);
	ft_bzero((void *)*thread_tab, sizeof(pthread_t) * (philo_info.nb_philo + 1));
	*mutex_tabs = (t_mutex_tabs *)malloc(sizeof(t_mutex_tabs));
	if (*mutex_tabs == NULL)
		return (EXIT_FAILURE);
	ft_bzero((void *)*mutex_tabs, sizeof(t_mutex_tabs));
	(*mutex_tabs)->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* (philo_info.nb_philo));
	if ((*mutex_tabs)->fork == NULL)
		return (EXIT_FAILURE);
	(*mutex_tabs)->time_last_meal = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* (philo_info.nb_philo));
	if ((*mutex_tabs)->time_last_meal == NULL)
		return (EXIT_FAILURE);
	(*mutex_tabs)->nb_must_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* (philo_info.nb_philo));
	if ((*mutex_tabs)->nb_must_eat == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_init_mutex_tabs(t_philo_info philo_info, t_mutex_tabs *mutex_tabs)
{
	int	i;

	i = 0;
	while (i < philo_info.nb_philo)
		if (pthread_mutex_init(mutex_tabs->fork + i++, NULL))
			return (EXIT_FAILURE);
	i = 0;
	while (i < philo_info.nb_philo)
		if (pthread_mutex_init(mutex_tabs->time_last_meal + i++, NULL))
			return (EXIT_FAILURE);
	i = 0;
	while (i < philo_info.nb_philo)
		if (pthread_mutex_init(mutex_tabs->nb_must_eat + i++, NULL))
			return (EXIT_FAILURE);
	if (pthread_mutex_init(&mutex_tabs->io, NULL))
			return (EXIT_FAILURE);
	if (pthread_mutex_init(&mutex_tabs->is_a_philo_dead, NULL))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_philo_thread_arg	*ft_set_philo_arg(t_philo_info philo_info,
	t_mutex_tabs *mutex_tabs, int nb_thread, t_bool *is_a_philo_dead)
{
	t_philo_thread_arg	*thread_arg;
	t_philo_info	*philo_info_cpy;
	struct timeval	*time_last_meal;

	thread_arg = (t_philo_thread_arg *)malloc(sizeof(t_philo_thread_arg));
	if (thread_arg == NULL)
		return (NULL);
	ft_bzero((void *)thread_arg, sizeof(t_philo_thread_arg));
	philo_info_cpy = (t_philo_info *)malloc(sizeof(t_philo_info));
	if (philo_info_cpy == NULL)
		return (free(thread_arg), NULL);
	time_last_meal = (struct timeval *)malloc(sizeof(struct timeval));
	if (time_last_meal == NULL)
		return (free(thread_arg), free(philo_info_cpy), NULL);
	if (ft_update_last_meal_time(nb_thread, mutex_tabs,
		time_last_meal))
		return (free(thread_arg), free(philo_info_cpy), free(time_last_meal), NULL);
	philo_info_cpy->nb_philo = philo_info.nb_philo;
	philo_info_cpy->time_to_die = philo_info.time_to_die;
	philo_info_cpy->time_to_eat = philo_info.time_to_eat;
	philo_info_cpy->time_to_sleep = philo_info.time_to_sleep;
	philo_info_cpy->nb_must_eat = philo_info.nb_must_eat;
	philo_info_cpy->init_time = philo_info.init_time;
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
		death_thread_arg->time_last_meal = (struct timeval **)malloc(sizeof(struct timeval *)
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

static void	ft_free_thread_arg(t_philo_thread_arg **philo_thread_arg,
	t_death_thread_arg **death_thread_arg)
{
	if (philo_thread_arg == NULL || death_thread_arg == NULL)
		return ;
	free((*philo_thread_arg)->time_last_meal);
	free((*philo_thread_arg)->philo_info);
	free (*philo_thread_arg);
	free(*death_thread_arg);
	*philo_thread_arg = NULL;
	*death_thread_arg = NULL; 
}

int	ft_create_thread(t_philo_info philo_info, pthread_t **thread_tab, 
	t_mutex_tabs *mutex_tabs)
{
	t_philo_thread_arg	*philo_thread_arg;
	t_death_thread_arg	*death_thread_arg;
	int					nb_thread;
	t_bool				is_a_philo_dead;

	philo_thread_arg = NULL;
	death_thread_arg = NULL;
	nb_thread = 0;
	is_a_philo_dead = false;
	while (nb_thread < philo_info.nb_philo)
	{
		philo_thread_arg = ft_set_philo_arg(philo_info, mutex_tabs, nb_thread, &is_a_philo_dead);
		if (philo_thread_arg == NULL)
			return (ft_free_thread_arg(&philo_thread_arg, &death_thread_arg), EXIT_FAILURE);
		death_thread_arg = ft_set_death_arg(philo_info, mutex_tabs, philo_thread_arg, death_thread_arg);
		if (philo_thread_arg == NULL)
			return (ft_free_thread_arg(&philo_thread_arg, &death_thread_arg), EXIT_FAILURE);
		if (pthread_create(*thread_tab + nb_thread, NULL, &ft_philo, (void *)philo_thread_arg))
			return (ft_free_thread_arg(&philo_thread_arg, &death_thread_arg), EXIT_FAILURE);
		nb_thread++;
	}
	if (pthread_create(*thread_tab + nb_thread, NULL, &ft_death, (void *)death_thread_arg))
		return (ft_free_thread_arg(NULL, &death_thread_arg), EXIT_FAILURE);
	if (ft_thread_join(philo_info, thread_tab))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_thread_join(t_philo_info philo_info, pthread_t **thread_tab)
{
	int	return_value;

	if (*thread_tab == NULL)
		return (EXIT_SUCCESS);
	return_value = EXIT_SUCCESS;
	while (1 + philo_info.nb_philo--)
		if (pthread_join((*thread_tab)[1 + philo_info.nb_philo], NULL))
			return_value = EXIT_FAILURE;
	free(*thread_tab);
	*thread_tab = NULL;
	return (return_value);
}

int	ft_destroy_mutex_tab(t_philo_info philo_info, t_mutex_tabs **mutex_tabs)
{
	int	return_value;
	int	i;

	if (*mutex_tabs == NULL)
		return (EXIT_SUCCESS);
	return_value = EXIT_SUCCESS;
	i = 0;
	while (i < philo_info.nb_philo)
	{
		if (pthread_mutex_destroy((*mutex_tabs)->fork + i))
			return_value = EXIT_FAILURE;
		if (pthread_mutex_destroy((*mutex_tabs)->time_last_meal + i))
			return_value = EXIT_FAILURE;
		if (pthread_mutex_destroy((*mutex_tabs)->nb_must_eat + i))
			return_value = EXIT_FAILURE;
		i++;
	}
	if (pthread_mutex_destroy(&(*mutex_tabs)->io))
			return_value = EXIT_FAILURE;
	if (pthread_mutex_destroy(&(*mutex_tabs)->is_a_philo_dead))
			return_value = EXIT_FAILURE;
	free((*mutex_tabs)->fork);
	free((*mutex_tabs)->time_last_meal);
	free((*mutex_tabs)->nb_must_eat);
	free(*mutex_tabs);
	*mutex_tabs = NULL;
	return (return_value);
}
