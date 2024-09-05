/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:08:38 by emichels          #+#    #+#             */
/*   Updated: 2024/07/08 17:58:09 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_c(char *str, int c)
{
	size_t	i;

	if (str[1] == '\0')
		return (0);
	i = 0;
	while (str && str[i] != (char)c)
	{
		if (str[i + 1] == '\0')
			break ;
		i++;
	}
	return (i);
}
