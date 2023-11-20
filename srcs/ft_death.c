/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 04:11:51 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/19 20:20:53 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static t_bool	ft_are_philo_done(t_philo_info philo_info,
	t_mutex_tabs *mutex_tabs, int **nb_must_eat)
{
	int		i;
	t_bool	philo_are_done;

	i = 0;
	philo_are_done = false;
	if (philo_info.nb_must_eat == NO_LIMIT)
		return (false);
	while (philo_are_done == false && i < philo_info.nb_philo)
	{
		if (pthread_mutex_lock(mutex_tabs->nb_must_eat + i))
			return (EXIT_FAILURE);
		if (*nb_must_eat[i] == 0)
			philo_are_done = true;
		if (pthread_mutex_unlock(mutex_tabs->nb_must_eat + i))
			return (EXIT_FAILURE);
		i++;
	}
	return (philo_are_done);
}

void	*ft_death(void *thread_arg_void)
{
	t_death_thread_arg	*thread_arg;
	t_bool				is_a_philo_dead;
	int					i;
	struct timeval		time;
	time_t				time_stamp;
	
	thread_arg = (t_death_thread_arg *)thread_arg_void;
	is_a_philo_dead = false;
	while (is_a_philo_dead == false
		&& ft_are_philo_done(thread_arg->philo_info, thread_arg->mutex_tabs,
			thread_arg->nb_must_eat) == false)
	{
		i = 0;
		while (i < thread_arg->philo_info.nb_philo)
		{
			if (gettimeofday(&time, NULL))
				return (NULL); //gerer les leaks
			if (pthread_mutex_lock(thread_arg->mutex_tabs->time_last_meal + i))
				return (NULL);
			time_stamp = 1000 * (time.tv_sec - (*thread_arg->time_last_meal[i]).tv_sec)
				+ (time.tv_usec  - (*thread_arg->time_last_meal[i]).tv_usec) / 1000;
			if (pthread_mutex_unlock(thread_arg->mutex_tabs->time_last_meal + i))
				return (NULL);
			if (time_stamp > thread_arg->philo_info.time_to_die)
				is_a_philo_dead = true;
			if (is_a_philo_dead == true)
			{
				if (pthread_mutex_lock(&thread_arg->mutex_tabs->is_a_philo_dead))
					return (NULL);
				*thread_arg->is_a_philo_dead = true;
				if (pthread_mutex_unlock(&thread_arg->mutex_tabs->is_a_philo_dead))
					return (NULL);
				if (ft_print_locked("has died", &thread_arg->philo_info, thread_arg->mutex_tabs, i, NULL))
					return (NULL);
				break ;
			}
			i++;
		}
	}
	free(thread_arg->time_last_meal);
	free(thread_arg->nb_must_eat);
	free (thread_arg);
	return (NULL);
}
