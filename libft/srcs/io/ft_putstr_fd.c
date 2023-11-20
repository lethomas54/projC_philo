/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:08:14 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/17 16:24:02 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return (1);
	while (*s)
		if (ft_putchar_fd (*(s++), fd))
			return (1);
	return (0);
}
