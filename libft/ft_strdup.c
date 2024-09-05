/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:06:30 by emichels          #+#    #+#             */
/*   Updated: 2024/06/17 14:57:57 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	char	*temp;

	temp = dest;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = 0;
	return (temp);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*copy;

	len = 0;
	while (s1[len])
		len++;
	copy = malloc(sizeof(char) * (len + 1));
	if (copy != NULL)
		ft_strcpy(copy, s1);
	else
		return (NULL);
	return (copy);
}
