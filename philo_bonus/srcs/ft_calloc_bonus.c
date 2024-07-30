/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:04:14 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 13:55:26 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pt;

	if ((size && count > SIZE_MAX / size))
		return (NULL);
	pt = malloc (count * size);
	if (!pt)
		return (NULL);
	ft_bzero (pt, count * size);
	return (pt);
}
