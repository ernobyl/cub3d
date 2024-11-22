/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_map_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:13:19 by emichels          #+#    #+#             */
/*   Updated: 2024/11/22 12:20:23 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*run_map_gen(char *argv)
{
	if (ft_strncmp(argv, "random", 6) == 0)
	{
		generator_map();
		argv = "maps/rand_map.cub";
	}
	return (argv);
}
