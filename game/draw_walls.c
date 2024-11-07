/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:16:08 by msilfver          #+#    #+#             */
/*   Updated: 2024/11/07 15:49:27 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_textured_wall_north(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray)
{
	float texture_x;
	float texture_y;
	float texture_step;
	uint32_t color;
	mlx_texture_t *texture;
	int texel_y;
	int texel;
	int y;

	texture = map->textures->wall_no;
	if (texture == NULL)
		return;
	texture_x = ray->ray_x - floor(ray->ray_x);
	texture_x *= texture->width;
	texture_step = (float)texture->height / (wall_bottom - wall_top);
	texture_y = 0.0f;
	y = wall_top;
	while (y < wall_bottom)
	{
		texel_y = (int)texture_y % texture->height;
		texel = texel_y * texture->width + (int)texture_x;
		color = ((uint32_t *)texture->pixels)[texel];
		color = apply_shading(color, 1.0f / (ray->distance * 0.5f));
		mlx_put_pixel(map->images->screen, ray_index, y, color);
		texture_y += texture_step;
		y++;
	}
}

void draw_textured_wall_south(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray)
{
	float texture_x;
	float texture_y;
	float texture_step;
	uint32_t color;
	mlx_texture_t *texture;
	int texel_y;
	int texel;
	int y;

	texture = map->textures->wall_so;
	if (texture == NULL)
		return;
	texture_x = ray->ray_x - floor(ray->ray_x);
	texture_x *= texture->width;
	texture_step = (float)texture->height / (wall_bottom - wall_top);
	texture_y = 0.0f;
	y = wall_top;
	while (y < wall_bottom)
	{
		texel_y = (int)texture_y % texture->height;
		texel = texel_y * texture->width + (int)texture_x;
		color = ((uint32_t *)texture->pixels)[texel];
		color = apply_shading(color, 1.0f / (ray->distance * 0.5f));
		mlx_put_pixel(map->images->screen, ray_index, y, color);
		texture_y += texture_step;
		y++;
	}
}

void draw_textured_wall_east(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray)
{
	float texture_x;
	float texture_y;
	float texture_step;
	uint32_t color;
	mlx_texture_t *texture;
	int texel_y;
	int texel;
	int y;

	texture = map->textures->wall_ea;
	if (texture == NULL)
		return;
	texture_x = ray->ray_y - floor(ray->ray_y);
	texture_x *= texture->width;
	texture_step = (float)texture->height / (wall_bottom - wall_top);
	texture_y = 0.0f;
	y = wall_top;
	while (y < wall_bottom)
	{
		texel_y = (int)texture_y % texture->height;
		texel = texel_y * texture->width + (int)texture_x;
		color = ((uint32_t *)texture->pixels)[texel];
		color = apply_shading(color, 1.0f / (ray->distance * 0.5f));
		mlx_put_pixel(map->images->screen, ray_index, y, color);
		texture_y += texture_step;
		y++;
	}
}

void draw_textured_wall_west(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray)
{
	float texture_x;
	float texture_y;
	float texture_step;
	uint32_t color;
	mlx_texture_t *texture;
	int texel_y;
	int texel;
	int y;

	texture = map->textures->wall_we;
	if (texture == NULL)
		return;
	texture_x = ray->ray_y - floor(ray->ray_y);
	texture_x *= texture->width;
	texture_step = (float)texture->height / (wall_bottom - wall_top);
	texture_y = 0.0f;
	y = wall_top;
	while (y < wall_bottom)
	{
		texel_y = (int)texture_y % texture->height;
		texel = texel_y * texture->width + (int)texture_x;
		color = ((uint32_t *)texture->pixels)[texel];
		color = apply_shading(color, 1.0f / (ray->distance * 0.5f));
		mlx_put_pixel(map->images->screen, ray_index, y, color);
		texture_y += texture_step;
		y++;
	}
}








