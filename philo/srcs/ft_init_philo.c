/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:17:16 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/05 12:26:19 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_create_tabs(t_info info, pthread_t **thread_tab,
	t_mutex_tabs *mutex_tabs)
{
	*thread_tab = NULL;
	*thread_tab = (pthread_t *)ft_calloc((info.nb_philo), sizeof(pthread_t));
	if (*thread_tab == NULL)
		return (EXIT_FAILURE);
	mutex_tabs->fork = (pthread_mutex_t *)ft_calloc(info.nb_philo,
			sizeof(pthread_mutex_t));
	if (mutex_tabs->fork == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_init_mutex_tabs(t_info info, t_mutex_tabs *mutex_tabs)
{
	int	i;

	i = 0;
	while (i < info.nb_philo)
		if (pthread_mutex_init(mutex_tabs->fork + i++, NULL))
			return (EXIT_FAILURE);
	if (pthread_mutex_init(&mutex_tabs->io, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&mutex_tabs->is_a_philo_dead, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_init_philo(t_info info, pthread_t **thread_tab,
	t_mutex_tabs *mutex_tabs)
{
	if (ft_create_tabs(info, thread_tab, mutex_tabs))
		return (EXIT_FAILURE);
	if (ft_init_mutex_tabs(info, mutex_tabs))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
