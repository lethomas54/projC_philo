/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_info_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:24:28 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 15:10:07 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher_bonus.h"

int	ft_set_info(int argc, char **argv, t_info *info)
{
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	info->nb_philo = ft_atoi(argv[1], 0);
	info->time_to_die = ft_atoi(argv[2], 0);
	info->time_to_eat = ft_atoi(argv[3], 0);
	info->time_to_sleep = ft_atoi(argv[4], 0);
	info->nb_must_eat = 1;
	if (argc == 6)
		info->nb_must_eat = ft_atoi(argv[5], 0);
	if (info->nb_philo <= 0
		|| info->time_to_die <= 0
		|| info->time_to_sleep <= 0
		|| info->nb_must_eat <= 0)
		return (EXIT_FAILURE);
	if (info->nb_philo == INT_MAX
		|| info->time_to_die == INT_MAX
		|| info->time_to_sleep == INT_MAX
		|| info->nb_must_eat == INT_MAX)
		return (EXIT_FAILURE);
	if (argc == 5)
		info->nb_must_eat = NO_LIMIT;
	if (ft_get_time(&info->init_time))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
