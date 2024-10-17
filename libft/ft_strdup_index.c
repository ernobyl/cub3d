/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:35:49 by emichels          #+#    #+#             */
/*   Updated: 2024/10/17 14:00:09 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_index(const char *src, int start)
{
	int		len;
	int		len2;
	char	*dup;

	if (!src || start < 0 || start >= (int)ft_strlen(src))
		return (NULL);
	len = ft_strlen(src + start);
	len2 = ft_strlen(src - start);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, src + start, len2 + 1);
	return (dup);
}
