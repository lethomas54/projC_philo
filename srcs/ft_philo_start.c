/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:00:30 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/19 18:24:51 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int ft_philo_start(t_philo_info philo_info, pthread_t **thread_tab,
	t_mutex_tabs **mutex_tabs)
{
	if (ft_create_tabs(philo_info, thread_tab, mutex_tabs))
		return (EXIT_FAILURE);
	if (ft_init_mutex_tabs(philo_info, *mutex_tabs))
		return (EXIT_FAILURE);
	if (ft_create_thread(philo_info, thread_tab, *mutex_tabs))
		return (EXIT_FAILURE);
	if (ft_destroy_mutex_tab(philo_info, mutex_tabs))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
