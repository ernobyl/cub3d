/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:39:41 by emichels          #+#    #+#             */
/*   Updated: 2024/09/26 13:15:16 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	display_player(t_map *map)
{
	map->images = ft_calloc(1, sizeof(t_image));
	mlx_put_pixel(map->images->mini_p, map->plr_x, map->plr_y, 24);
}