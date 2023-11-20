/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_philo_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:18:07 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/19 19:50:54 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_set_philo_info(int argc, char **argv, t_philo_info *philo_info)
{
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	philo_info->nb_philo = ft_atoi(argv[1], 0);
	philo_info->time_to_die = ft_atoi(argv[2], 0);
	philo_info->time_to_eat = ft_atoi(argv[3], 0);
	philo_info->time_to_sleep = ft_atoi(argv[4], 0);
	philo_info->nb_must_eat = 0;
	if (argc == 6)
		philo_info->nb_must_eat = ft_atoi(argv[5], 0);
	if (philo_info->nb_philo < 0
		|| philo_info->time_to_die < 0
		|| philo_info->time_to_sleep < 0
		|| philo_info->nb_must_eat < 0)
		return (EXIT_FAILURE);
	if (philo_info->nb_philo == INT_MAX
		|| philo_info->time_to_die == INT_MAX
		|| philo_info->time_to_sleep == INT_MAX
		|| philo_info->nb_must_eat == INT_MAX)
		return (EXIT_FAILURE);
	if (argc == 5)
		philo_info->nb_must_eat = NO_LIMIT;
	if (gettimeofday(&philo_info->init_time, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
