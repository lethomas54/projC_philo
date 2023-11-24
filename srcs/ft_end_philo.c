/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:41:19 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/22 02:07:42 by lethomas         ###   ########.fr       */
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

static int	ft_destroy_mutex_tab(t_info info, t_mutex_tabs **mutex_tabs)
{
	int	return_value;
	int	i;

	if (*mutex_tabs == NULL)
		return (EXIT_SUCCESS);
	return_value = EXIT_SUCCESS;
	i = 0;
	while (i < info.nb_philo)
	{
		if (pthread_mutex_destroy((*mutex_tabs)->fork + i))
			return_value = EXIT_FAILURE;
		if (pthread_mutex_destroy((*mutex_tabs)->time_last_meal + i))
			return_value = EXIT_FAILURE;
		i++;
	}
	if (pthread_mutex_destroy(&(*mutex_tabs)->io))
			return_value = EXIT_FAILURE;
	if (pthread_mutex_destroy(&(*mutex_tabs)->is_a_philo_dead))
			return_value = EXIT_FAILURE;
	free((*mutex_tabs)->fork);
	free((*mutex_tabs)->time_last_meal);
	free(*mutex_tabs);
	*mutex_tabs = NULL;
	return (return_value);
}

int	ft_end_philo(t_info *info,  pthread_t **thread_tab, t_mutex_tabs **mutex_tabs)
{
	int	return_value;
	
	return_value = EXIT_SUCCESS;
	if (ft_thread_join(*info, thread_tab))
		return_value = EXIT_FAILURE;
	if (ft_destroy_mutex_tab(*info, mutex_tabs))
		return_value = EXIT_FAILURE;
	return (return_value);
}
