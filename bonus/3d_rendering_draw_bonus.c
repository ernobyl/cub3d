/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_rendering_draw_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:02:44 by msilfver          #+#    #+#             */
/*   Updated: 2024/12/02 16:22:04 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_floors(t_map *map, int wall_bottom)
{
	int	y;

	y = wall_bottom;
	while (y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(map->images->screen, map->ray_index,
			y, map->images->color_floor);
		y++;
	}
}

int	check_for_textures(t_map *map, mlx_texture_t *texture)
{
	if (map->textures == NULL)
		return (1);
	if (texture == NULL)
		return (1);
	return (0);
}

void	draw_walls(t_map *map, int wall_top, int wall_bottom, t_ray *ray)
{
	safe_check(ray->ray_index, map->rays);
	if (ray->hit_e == 1
		&& check_for_textures(map, map->textures->wall_ea) == 0)
		draw_textured_wall_east(map, wall_top, wall_bottom, ray);
	else if (ray->hit_w == 1
		&& check_for_textures(map, map->textures->wall_we) == 0)
		draw_textured_wall_west(map, wall_top, wall_bottom, ray);
	else if (ray->hit_s == 1
		&& check_for_textures(map, map->textures->wall_so) == 0)
		draw_textured_wall_south(map, wall_top, wall_bottom, ray);
	else if (ray->hit_n == 1
		&& check_for_textures(map, map->textures->wall_no) == 0)
		draw_textured_wall_north(map, wall_top, wall_bottom, ray);
}
