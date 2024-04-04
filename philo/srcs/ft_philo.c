/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:32:58 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/09 01:04:14 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_philo_simu(t_philo_arg *arg)
{
	t_bool	is_a_philo_dead;
	int		nb_eat_left;

	is_a_philo_dead = false;
	nb_eat_left = arg->info->nb_must_eat;
	while (nb_eat_left != 0
		&& is_a_philo_dead == false)
	{
		if (is_a_philo_dead == false
			&& ft_philo_thinking(arg, &is_a_philo_dead))
			return (EXIT_FAILURE);
		if (is_a_philo_dead == false
			&& ft_philo_eating(arg, &nb_eat_left, &is_a_philo_dead))
			return (EXIT_FAILURE);
		if (is_a_philo_dead == false
			&& ft_philo_sleeping(arg, &is_a_philo_dead))
			return (EXIT_FAILURE);
		if (is_a_philo_dead == false
			&& ft_is_a_philo_dead(arg, &is_a_philo_dead))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	*ft_philo(void *thread_arg_void)
{
	int			return_value;
	t_philo_arg	*thread_arg;

	return_value = EXIT_SUCCESS;
	(void)return_value;
	thread_arg = (t_philo_arg *)thread_arg_void;
	if (ft_philo_simu(thread_arg))
		return_value = EXIT_FAILURE;
	free(thread_arg->time_last_meal);
	free(thread_arg);
	return (NULL);
}
