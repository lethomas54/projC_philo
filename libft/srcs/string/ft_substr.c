/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:26:21 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/17 16:24:02 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new_s;

	if (!s)
		return (NULL);
	if (start > ft_strlen (s))
		new_s = (char *)malloc (sizeof (char) * 1);
	else if (ft_strlen (&s[start]) < len)
		new_s = (char *)malloc (sizeof (char) * (ft_strlen (&s[start]) + 1));
	else
		new_s = (char *)malloc (sizeof (char) * (len + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < len && start < ft_strlen (s))
		new_s[i++] = s[start++];
	new_s[i] = 0;
	return (new_s);
}
