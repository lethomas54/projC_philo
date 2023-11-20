/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:24:24 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/17 16:24:02 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new_s;

	if (!s || !f)
		return (NULL);
	i = 0;
	new_s = (char *)malloc (sizeof (char) * (ft_strlen (s) + 1));
	if (!new_s)
		return (NULL);
	while (*s)
	{
		new_s[i] = (*f)(i, *(s++));
		i++;
	}
	new_s[i] = 0;
	return (new_s);
}
