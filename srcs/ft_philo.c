/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 22:32:58 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/23 17:40:35 by lethomas         ###   ########.fr       */
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
			&& ft_philo_spleeping(arg, &is_a_philo_dead))
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
	thread_arg = (t_philo_arg *)thread_arg_void;
	if (ft_philo_simu(thread_arg))
		return_value = EXIT_FAILURE;
	free(thread_arg->time_last_meal);
	free(thread_arg);
	return (NULL);
}
