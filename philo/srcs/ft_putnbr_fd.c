/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:07:41 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 12:24:50 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	ft_putnbr_sub(int nb, int sign, int fd)
{
	if (nb / 10)
		if (ft_putnbr_sub (nb / 10, sign, fd))
			return (1);
	if (ft_putchar_fd ('0' + sign * (nb % 10), fd))
		return (1);
	return (0);
}

int	ft_putnbr_fd(int nb, int fd)
{
	int	sign;

	sign = 1;
	if (fd < 0)
		return (1);
	if (nb < 0)
	{
		sign = -1;
		if (ft_putchar_fd ('-', fd))
			return (1);
	}
	if (ft_putnbr_sub (nb, sign, fd))
		return (1);
	return (0);
}
