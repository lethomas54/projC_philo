/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:32:58 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/15 17:13:43 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_philo_simulation(t_philo *philo)
{
	while (philo->nb_meal_left != 0)
	{
		if (ft_philo_eating(philo))
			return (EXIT_FAILURE);
		if (ft_philo_sleeping(philo))
			return (EXIT_FAILURE);
		if (ft_philo_thinking(philo))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_philo(t_philo *philo)
{
	pthread_t	death;
	void		*death_return_value_pt;
	int			return_value;

	death_return_value_pt = NULL;
	return_value = EXIT_SUCCESS;
	if (pthread_create(&death, NULL, &ft_death, (void *)philo))
	{
		pthread_mutex_destroy(&philo->mutex_death);
		return (EXIT_FAILURE);
	}
	if (ft_philo_simulation(philo)
		|| pthread_join(death, &death_return_value_pt))
		return_value = EXIT_FAILURE;
	if (pthread_mutex_destroy(&philo->mutex_death))
		return_value = EXIT_FAILURE;
	if (death_return_value_pt == NULL)
		return_value = EXIT_FAILURE;
	else
	{
		return_value = *((int *)death_return_value_pt);
		ft_free(&death_return_value_pt);
	}
	return (return_value);
}
