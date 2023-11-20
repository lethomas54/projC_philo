/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:02:29 by lethomas          #+#    #+#             */
/*   Updated: 2023/11/17 16:24:02 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen (src);
	if (!dstsize && !dst)
		return (src_len);
	dst_len = ft_strlen (dst);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while ((dstsize - dst_len - 1 - i > 0) && *src)
		dst[dst_len + i++] = *(src++);
	dst[dst_len + i] = 0;
	return (dst_len + src_len);
}
