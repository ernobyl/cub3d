/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_rendering_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:26:09 by emichels          #+#    #+#             */
/*   Updated: 2024/11/24 17:46:04 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_3d_screen(t_map *map)
{
	map->images->screen = mlx_new_image(map->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!map->images->screen)
		struct_error("Failed to allocate screen image\n", map);
	safe_img_to_window(map, map->images->screen, 0, 0);
}

static void	draw_ray_slice(t_map *map, t_ray *ray)
{
	int		wall_height;
	int		wall_top;
	int		wall_bottom;

	ray->perpendicular_distance = ray->distance
		* fabs(cos(ray->angle - map->plr_angle));
	if (ray->perpendicular_distance < 0.1f)
		ray->perpendicular_distance = 0.1f;
	wall_height = (int)(SCREEN_HEIGHT / ray->perpendicular_distance);
	wall_top = (SCREEN_HEIGHT / 2) - (wall_height / 2);
	wall_bottom = (SCREEN_HEIGHT / 2) + (wall_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > SCREEN_HEIGHT)
		wall_bottom = SCREEN_HEIGHT;
	draw_walls(map, wall_top, wall_bottom, ray);
	draw_floors(map, wall_bottom);
}

void	draw_3d_scene(t_map *map)
{
	t_ray	*ray;

	map->ray_index = 0;
	while (map->ray_index < SCREEN_WIDTH)
	{
		ray = &map->rays[map->ray_index];
		if (ray->distance > 0)
			draw_ray_slice(map, ray);
		map->ray_index++;
	}
}
