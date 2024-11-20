/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_to_slice_loops.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:18:05 by emichels          #+#    #+#             */
/*   Updated: 2024/11/20 21:54:58 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
