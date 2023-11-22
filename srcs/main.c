/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 21:02:39 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/22 01:11:10 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	main(int argc, char **argv)
{
	t_philo_info	philo_info;
	pthread_t		*thread_tab;
	t_mutex_tabs	*mutex_tabs;

	if (ft_set_philo_info(argc, argv, &philo_info))
		return (ft_putendl_fd("philo: invalid argument", 2), EXIT_FAILURE);
	if (ft_philo_start(philo_info, &thread_tab, &mutex_tabs))
	{
		free(thread_tab);
		free(mutex_tabs);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
// plutot que free, utiliser destroy mutex et thread join. Mais il faut
// penser au cas ou certains mutex ou threads n ont pas pu etre crees
// penser au cas ou il y a un seul philosophe
// revoir la necessite d allouer pour chaque philo_info car cst : par de prob de race cdt
//		->finalement important pour nb_meal (uniquement a priori)