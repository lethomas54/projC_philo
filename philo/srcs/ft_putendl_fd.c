/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:07:12 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 12:24:47 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

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
