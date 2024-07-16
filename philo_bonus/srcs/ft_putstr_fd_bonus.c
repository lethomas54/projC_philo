/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:08:14 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 13:55:56 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher_bonus.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return (1);
	while (*s)
		if (ft_putchar_fd (*(s++), fd))
			return (1);
	return (0);
}
