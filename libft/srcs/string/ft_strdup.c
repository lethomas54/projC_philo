/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:11:54 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/17 16:24:02 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	size_t	src_len;
	char	*dst;

	i = 0;
	src_len = ft_strlen (src);
	dst = (char *)malloc (sizeof (char) * (src_len + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy (dst, src, src_len + 1);
	return (dst);
}
