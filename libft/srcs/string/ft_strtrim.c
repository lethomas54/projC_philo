/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:25:20 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/17 16:24:02 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_is_set(char c, char const *set)
{
	while (*set)
		if (c == *(set++))
			return (1);
	return (0);
}

char	*ft_strtrim(char const *str_trim, char const *set)
{
	int		n_begin;
	int		n_end;

	if (!str_trim || !set)
		return (NULL);
	n_begin = 0;
	while (ft_is_set (str_trim[n_begin], set))
		n_begin++;
	n_end = n_begin;
	while (str_trim[n_end])
		n_end++;
	n_end--;
	while (ft_is_set (str_trim[n_end], set))
		n_end--;
	return (ft_substr (str_trim, n_begin, n_end - n_begin + 1));
}
