/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:41:19 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/07 12:13:37 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

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
		i++;
	}
	if (pthread_mutex_destroy(&(*mutex_tabs)->io))
		return_value = EXIT_FAILURE;
	if (pthread_mutex_destroy(&(*mutex_tabs)->is_a_philo_dead))
		return_value = EXIT_FAILURE;
	free((*mutex_tabs)->fork);
	free(*mutex_tabs);
	*mutex_tabs = NULL;
	return (return_value);
}

int	ft_end_philo(t_info *info, t_mutex_tabs **mutex_tabs)
{
	int	return_value;

	return_value = EXIT_SUCCESS;
	if (ft_destroy_mutex_tab(*info, mutex_tabs))
		return_value = EXIT_FAILURE;
	return (return_value);
}
