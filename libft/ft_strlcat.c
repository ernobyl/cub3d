/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:06:15 by emichels          #+#    #+#             */
/*   Updated: 2023/11/15 10:39:19 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	count_d;
	size_t	count_s;

	if (dstsize <= ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	count_d = ft_strlen(dst);
	count_s = 0;
	while (src[count_s] && count_d + 1 < dstsize)
		dst[count_d++] = src[count_s++];
	dst[count_d] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[count_s]));
}
