/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:17:16 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/22 01:23:52 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_create_tabs(t_philo_info philo_info, pthread_t **thread_tab,
	t_mutex_tabs **mutex_tabs)
{
	*thread_tab = NULL;
	*mutex_tabs = NULL;
	*thread_tab = (pthread_t *)calloc((philo_info.nb_philo + 1),
		sizeof(pthread_t));
	if (*thread_tab == NULL)
		return (EXIT_FAILURE);
	*mutex_tabs = (t_mutex_tabs *)calloc(1, sizeof(t_mutex_tabs));
	if (*mutex_tabs == NULL)
		return (EXIT_FAILURE);
	(*mutex_tabs)->fork = (pthread_mutex_t *)calloc((philo_info.nb_philo),
		sizeof(pthread_mutex_t));
	if ((*mutex_tabs)->fork == NULL)
		return (EXIT_FAILURE);
	(*mutex_tabs)->time_last_meal = (pthread_mutex_t *)
		calloc((philo_info.nb_philo), sizeof(pthread_mutex_t));
	if ((*mutex_tabs)->time_last_meal == NULL)
		return (EXIT_FAILURE);
	(*mutex_tabs)->nb_must_eat = (pthread_mutex_t *)
		calloc((philo_info.nb_philo), sizeof(pthread_mutex_t));
	if ((*mutex_tabs)->nb_must_eat == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_init_mutex_tabs(t_philo_info philo_info, t_mutex_tabs *mutex_tabs)
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

int	ft_init_philo(t_philo_info philo_info, pthread_t **thread_tab,
	t_mutex_tabs **mutex_tabs)
{
	if (ft_create_tabs(philo_info, thread_tab, mutex_tabs))
		return (EXIT_FAILURE);
	if (ft_init_mutex_tabs(philo_info, *mutex_tabs))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}