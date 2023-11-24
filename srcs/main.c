/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:02:39 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/23 17:15:35 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_set_info(int argc, char **argv, t_info *info)
{
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	info->nb_philo = ft_atoi(argv[1], 0);
	info->time_to_die = ft_atoi(argv[2], 0);
	info->time_to_eat = ft_atoi(argv[3], 0);
	info->time_to_sleep = ft_atoi(argv[4], 0);
	info->nb_must_eat = 0;
	if (argc == 6)
		info->nb_must_eat = ft_atoi(argv[5], 0);
	if (info->nb_philo < 0
		|| info->time_to_die < 0
		|| info->time_to_sleep < 0
		|| info->nb_must_eat < 0)
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

static int ft_philo_program(t_info *info, pthread_t **thread_tab,
	t_mutex_tabs **mutex_tabs)
{
	if (ft_init_philo(info, thread_tab, mutex_tabs))
		return (EXIT_FAILURE);
	if (ft_create_philo(info, thread_tab, *mutex_tabs))
		return (EXIT_FAILURE);
	if (ft_end_philo(info, thread_tab, mutex_tabs))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	info;
	pthread_t		*thread_tab;
	t_mutex_tabs	*mutex_tabs;

	if (ft_set_info(argc, argv, &info))
		return (EXIT_FAILURE);
	if (ft_philo_program(&info, &thread_tab, &mutex_tabs))
	{
		//free(thread_tab);
		//free(mutex_tabs);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// plutot que free, utiliser destroy mutex et thread join. Mais il faut
// penser au cas ou certains mutex ou threads n ont pas pu etre crees
// penser au cas ou il y a un seul philosophe
// revoir la necessite d allouer pour chaque info car cst : par de prob de race cdt
//		->finalement important pour nb_meal (uniquement a priori)