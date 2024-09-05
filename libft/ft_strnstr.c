/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:33:10 by emichels          #+#    #+#             */
/*   Updated: 2023/11/15 12:13:19 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	if (needle[0] == '\0')
		return ((char *)haystack);
	h = 0;
	while (h < len && haystack[h] != '\0')
	{
		n = 0;
		while ((h + n) < len && haystack[h + n] == needle[n])
		{
			if (needle[n + 1] == '\0')
				return ((char *)(haystack + h));
			n++;
		}
		h++;
	}
	return (0);
}
