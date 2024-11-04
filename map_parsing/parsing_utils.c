/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:49:33 by emichels          #+#    #+#             */
/*   Updated: 2024/11/04 11:51:52 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
			return (1);
		i++;
	}
	return (0);
}

void	alloc_images(t_map *map)
{
	map->images = ft_calloc(1, sizeof(t_image));
	if (!map->images)
		struct_error("Error\nmalloc failed\n", map);
	map->textures = ft_calloc(1, sizeof(t_texture));
	if (!map->textures)
		struct_error("Error\nmalloc failed\n", map);
}

void	init_plr_angle(t_map *map, char direction)
{
	if (direction == 'N')
		map->plr_angle = (3 * PI) / 2;
	else if (direction == 'S')
		map->plr_angle = PI / 2;
	else if (direction == 'W')
		map->plr_angle = PI;
	else if (direction == 'E')
		map->plr_angle = 0.0f;
}
