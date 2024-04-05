/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 02:24:21 by lethomas          #+#    #+#             */
/*   Updated: 2024/04/05 11:29:46 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
#include <limits.h>

int	ft_get_time(time_t *time)
{
	struct timeval	time_struct;

	if (gettimeofday(&time_struct, NULL))
		return (EXIT_FAILURE);
	*time = 1000 * time_struct.tv_sec + time_struct.tv_usec / 1000;
	return (EXIT_SUCCESS);
}
