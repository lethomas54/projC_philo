/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:02:39 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/05 21:30:18 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_set_info(int argc, char **argv, t_info *info)
{
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	info->philo_count = ft_atoi(argv[1], 0);
	info->starv_time = ft_atoi(argv[2], 0);
	info->eat_time = ft_atoi(argv[3], 0);
	info->sleep_time = ft_atoi(argv[4], 0);
	info->meal_left = 0;
	if (argc == 6)
		info->meal_left = ft_atoi(argv[5], 0);
	if (info->philo_count < 0
		|| info->starv_time < 0
		|| info->sleep_time < 0
		|| info->meal_left < 0)
		return (EXIT_FAILURE);
	if (info->philo_count == INT_MAX
		|| info->starv_time == INT_MAX
		|| info->sleep_time == INT_MAX
		|| info->meal_left == INT_MAX)
		return (EXIT_FAILURE);
	if (argc == 5)
		info->meal_left = NO_LIMIT;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_mutex		mutex;
	t_shared	shared;
	t_philo		*philo;
	int			exit_value;

	exit_value = EXIT_SUCCESS;
	if (ft_set_info(argc, argv, &info))
		return (ft_putendl_fd("invalid argument", 2), EXIT_FAILURE);
	if (ft_init_philo(info, &shared, &philo, &mutex)
		|| ft_create_thread(info.philo_count, &shared, philo))
		exit_value = EXIT_FAILURE;
	if (ft_free_destroy(info.philo_count, philo, &mutex))
		exit_value = EXIT_FAILURE;
	return (exit_value);
}
