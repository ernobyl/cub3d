/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_to_slice_loops.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:18:05 by emichels          #+#    #+#             */
/*   Updated: 2024/11/27 15:02:43 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	texture_to_slice_no(t_map *map, t_tex *t, int wall_bottom, t_ray *ray)
{
	uint32_t		color;
	mlx_texture_t	*texture;

	texture = map->textures->wall_no;
	while (t->y < wall_bottom)
	{
		t->texel_y = (int)t->texture_y % texture->height;
		t->texel = t->texel_y * texture->width + (int)t->texture_x;
		color = ((uint32_t *)texture->pixels)[t->texel];
		color = apply_shading(color, 1.0f / (ray->distance * 1.3f));
		mlx_put_pixel(map->images->screen, map->ray_index, t->y, color);
		t->texture_y += t->texture_step;
		t->y++;
	}
}

void	texture_to_slice_so(t_map *map, t_tex *t, int wall_bottom, t_ray *ray)
{
	uint32_t		color;
	mlx_texture_t	*texture;

	texture = map->textures->wall_so;
	while (t->y < wall_bottom)
	{
		t->texel_y = (int)t->texture_y % texture->height;
		t->texel = t->texel_y * texture->width + (int)t->texture_x;
		color = ((uint32_t *)texture->pixels)[t->texel];
		color = apply_shading(color, 1.0f / (ray->distance * 1.3f));
		mlx_put_pixel(map->images->screen, map->ray_index, t->y, color);
		t->texture_y += t->texture_step;
		t->y++;
	}
}

void	texture_to_slice_ea(t_map *map, t_tex *t, int wall_bottom, t_ray *ray)
{
	uint32_t		color;
	mlx_texture_t	*texture;

	texture = map->textures->wall_ea;
	while (t->y < wall_bottom)
	{
		t->texel_y = (int)t->texture_y % texture->height;
		t->texel = t->texel_y * texture->width + (int)t->texture_x;
		color = ((uint32_t *)texture->pixels)[t->texel];
		color = apply_shading(color, 1.0f / (ray->distance * 1.3f));
		mlx_put_pixel(map->images->screen, map->ray_index, t->y, color);
		t->texture_y += t->texture_step;
		t->y++;
	}
}

void	texture_to_slice_we(t_map *map, t_tex *t, int wall_bottom, t_ray *ray)
{
	uint32_t		color;
	mlx_texture_t	*texture;

	texture = map->textures->wall_we;
	while (t->y < wall_bottom)
	{
		t->texel_y = (int)t->texture_y % texture->height;
		t->texel = t->texel_y * texture->width + (int)t->texture_x;
		color = ((uint32_t *)texture->pixels)[t->texel];
		color = apply_shading(color, 1.0f / (ray->distance * 1.3f));
		mlx_put_pixel(map->images->screen, map->ray_index, t->y, color);
		t->texture_y += t->texture_step;
		t->y++;
	}
}
