/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:16:08 by msilfver          #+#    #+#             */
/*   Updated: 2024/11/20 20:32:18 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    init_tex_struct(t_tex *t)
{
	t->texture_x = 0;
	t->texture_y_start = 0;
	t->texture_step = 0;
	t->texture_y = 0;
	t->texel_y = 0;
	t->texel = 0;
	t->y = 0;
}

void	draw_textured_wall_north(t_map *map, int wall_top, int wall_bottom, t_ray *ray)
{
	t_tex			t;
	mlx_texture_t	*texture;

	texture = map->textures->wall_no;
	init_tex_struct(&t);
	if (texture == NULL)
		return;
	t.texture_x = ray->ray_x - floor(ray->ray_x);
	t.texture_x *= texture->width;
	float perpendicular_distance = ray->distance * fabs(cos(ray->angle - map->plr_angle));
	if (perpendicular_distance < 0.1f)
		perpendicular_distance = 0.1f;
	float wall_height = (float)SCREEN_HEIGHT / perpendicular_distance;
	t.texture_y_start = ((wall_top - (SCREEN_HEIGHT / 2 - wall_height / 2)) * texture->height) / wall_height;
	t.texture_step = (float)texture->height / wall_height;
	t.texture_y = t.texture_y_start;
	t.y = wall_top;
	texture_to_slice_no(map, &t, wall_bottom, ray);
}

void draw_textured_wall_south(t_map *map, int wall_top, int wall_bottom, t_ray *ray)
{
	t_tex			t;
	mlx_texture_t	*texture;

	texture = map->textures->wall_so;
	init_tex_struct(&t);
	if (texture == NULL)
		return;
	t.texture_x = ray->ray_x - floor(ray->ray_x);
	t.texture_x *= texture->width;
	float perpendicular_distance = ray->distance * fabs(cos(ray->angle - map->plr_angle));
	if (perpendicular_distance < 0.1f)
		perpendicular_distance = 0.1f;
	float wall_height = (float)SCREEN_HEIGHT / perpendicular_distance;
	t.texture_y_start = ((wall_top - (SCREEN_HEIGHT / 2 - wall_height / 2)) * texture->height) / wall_height;
	t.texture_step = (float)texture->height / wall_height;
	t.texture_y = t.texture_y_start;
	t.y = wall_top;
	texture_to_slice_so(map, &t, wall_bottom, ray);
}

void draw_textured_wall_east(t_map *map, int wall_top, int wall_bottom, t_ray *ray)
{
	t_tex			t;
	mlx_texture_t	*texture;

	texture = map->textures->wall_ea;
	init_tex_struct(&t);
	if (texture == NULL)
		return;
	t.texture_x = ray->ray_y - floor(ray->ray_y);
	t.texture_x *= texture->width;
	float perpendicular_distance = ray->distance * fabs(cos(ray->angle - map->plr_angle));
	if (perpendicular_distance < 0.1f)
		perpendicular_distance = 0.1f;
	float wall_height = (float)SCREEN_HEIGHT / perpendicular_distance;
	t.texture_y_start = ((wall_top - (SCREEN_HEIGHT / 2 - wall_height / 2)) * texture->height) / wall_height;
	t.texture_step = (float)texture->height / wall_height;
	t.texture_y = t.texture_y_start;
	t.y = wall_top;
	texture_to_slice_ea(map, &t, wall_bottom, ray);
}

void draw_textured_wall_west(t_map *map, int wall_top, int wall_bottom, t_ray *ray)
{
	t_tex			t;
	mlx_texture_t	*texture;

	texture = map->textures->wall_we;
	init_tex_struct(&t);
	if (texture == NULL)
		return;
	t.texture_x = ray->ray_y - floor(ray->ray_y);
	t.texture_x *= texture->width;
	float perpendicular_distance = ray->distance * fabs(cos(ray->angle - map->plr_angle));
	if (perpendicular_distance < 0.1f)
		perpendicular_distance = 0.1f;
	float wall_height = (float)SCREEN_HEIGHT / perpendicular_distance;
	t.texture_y_start = ((wall_top - (SCREEN_HEIGHT / 2 - wall_height / 2)) * texture->height) / wall_height;
	t.texture_step = (float)texture->height / wall_height;
	t.texture_y = t.texture_y_start;
	t.y = wall_top;
	texture_to_slice_we(map, &t, wall_bottom, ray);
}
