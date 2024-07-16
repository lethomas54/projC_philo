/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:05:54 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 12:26:02 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return (1);
	if (write (fd, &c, 1) < 0)
		return (1);
	return (0);
}
