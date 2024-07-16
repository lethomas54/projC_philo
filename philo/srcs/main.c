/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:02:39 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 19:12:31 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	set_info(int argc, char **argv, t_info *info)
{
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	info->count = ft_atoi(argv[1], 0);
	info->starv_time = ft_atoi(argv[2], 0);
	info->eat_time = ft_atoi(argv[3], 0);
	info->sleep_time = ft_atoi(argv[4], 0);
	info->meal_left = 1;
	if (argc == 6)
		info->meal_left = ft_atoi(argv[5], 0);
	if (info->count <= 0
		|| info->starv_time <= 0
		|| info->sleep_time <= 0
		|| info->meal_left <= 0)
		return (EXIT_FAILURE);
	if (info->count == INT_MAX
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
	t_sh	sh;
	t_philo		*philo;

	if (set_info(argc, argv, &info))
		return (ft_putendl_fd("invalid argument", 2), EXIT_FAILURE);
	if (init_philo(info, &sh, &philo, &mutex))
		return (EXIT_FAILURE);
	if (create_thread(info.count, &sh, philo))
		return (EXIT_FAILURE);
	if (free_destroy(info.count, philo, &mutex))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
