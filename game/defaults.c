/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:41:46 by emichels          #+#    #+#             */
/*   Updated: 2024/11/08 21:51:29 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_default_colors(t_map *map)
{
	map->images->color_ceiling = BLUE;
	map->images->color_floor = GREEN;
	map->images->color_wall = WHITE_TP;
}
