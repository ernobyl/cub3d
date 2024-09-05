/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:28:04 by emichels          #+#    #+#             */
/*   Updated: 2024/02/05 15:33:19 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free(char **tofree)
{
	int	i;

	i = -1;
	while (tofree[++i])
		free(tofree[i]);
	free(tofree);
}
