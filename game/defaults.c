/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:41:46 by emichels          #+#    #+#             */
/*   Updated: 2024/11/22 09:44:32 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_default_colors(t_map *map)
{
	map->images->color_ceiling = SKY_BLUE;
	map->images->color_floor = GRASS_GREEN;
	map->images->color_wall = WHITE_TP;
}

void	zero_map_struct(t_map *map)
{
	map->fd = 0;
	map->mlx = NULL;
	map->y = 0;
	map->x = 0;
	map->max_y = 0;
	map->max_x = 0;
	map->plr_y = 0.0f;
	map->plr_x = 0.0f;
	map->plr_angle = 0.0f;
	map->str = NULL;
	map->arr = NULL;
	map->images = NULL;
	map->textures = NULL;
	map->sprites = NULL;
	map->rays->angle = 0;
	map->rays->distance = 0;
	map->rays->hit_x = 0;
	map->rays->hit_y = 0;
}
