/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatjuhi <kmatjuhi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:13:06 by emichels          #+#    #+#             */
/*   Updated: 2024/06/10 21:27:18 by kmatjuhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		i2;
	char		*result;

	i = start;
	if (!*s || start > ft_strlen(s))
		return (ft_strdup(""));
	else
	{
		if (ft_strlen(s) - i < len)
			result = malloc(sizeof(char) * ft_strlen(s) - i + 1);
		else
			result = malloc(sizeof(char) * len + 1);
	}
	if (!result)
		return (NULL);
	i2 = 0;
	while (i2 < len && s[i])
	{
		result[i2] = (char)s[i];
		i++;
		i2++;
	}
	result[i2] = '\0';
	return (result);
}
