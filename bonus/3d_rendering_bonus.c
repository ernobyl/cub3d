/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_rendering_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:26:09 by emichels          #+#    #+#             */
/*   Updated: 2024/11/24 17:19:13 by msilfver         ###   ########.fr       */
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

uint32_t	apply_shading(uint32_t color, float shading_factor)
{
	int	r;
	int	g;
	int	b;
	int	a;

	if (shading_factor > 1.3f)
		shading_factor = 1.3f;
	else if (shading_factor < 0.2f)
		shading_factor = 0.2f;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	r = (int)(r * shading_factor);
	g = (int)(g * shading_factor);
	b = (int)(b * shading_factor);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

static void	draw_ray_slice(t_map *map, t_ray *ray)
{
	int		wall_height;
	int		wall_top;
	int		wall_bottom;
	float	shading_factor;

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
	shading_factor = 1.0f / (ray->perpendicular_distance * 0.5f);
	shading_factor = fmaxf(fminf(shading_factor, 1.0f), 0.2f);
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
