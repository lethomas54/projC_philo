/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:59:16 by lethomas          #+#    #+#             */
/*   Updated: 2024/07/16 12:23:22 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_atoi(const char *str, char alpha_term_allow)
{
	int			sign;
	long int	res;

	sign = 1;
	res = 0;
	while ((*str > 8 && *str < 14) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		res = 10 * res + sign * (*(str++) - '0');
		if (res <= INT_MIN)
			return (INT_MIN);
		if (res >= INT_MAX)
			return (INT_MAX);
	}
	if (!alpha_term_allow && *str != 0)
		return (INT_MAX);
	return ((int)res);
}
