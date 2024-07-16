/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:07:12 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 13:55:46 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher_bonus.h"

int	ft_putendl_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return (1);
	if (ft_putstr_fd (s, fd))
		return (1);
	if (ft_putchar_fd ('\n', fd))
		return (1);
	return (0);
}
