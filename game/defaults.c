/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:41:46 by emichels          #+#    #+#             */
/*   Updated: 2024/11/11 15:09:16 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_default_colors(t_map *map)
{
	map->images->color_ceiling = SKY_BLUE;
	map->images->color_floor = GRASS_GREEN;
	map->images->color_wall = WHITE_TP;
}
