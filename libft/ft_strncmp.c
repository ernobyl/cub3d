/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:57:35 by emichels          #+#    #+#             */
/*   Updated: 2024/01/17 15:06:35 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n != 0)
	{
		while (*s1 && *s2 && n > 0)
		{
			if (*s1 != *s2)
				return (*(unsigned char *)s1 - *(unsigned char *)s2);
			s1++;
			s2++;
			n--;
		}
	}
	if (n > 0)
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	else
		return (0);
}
