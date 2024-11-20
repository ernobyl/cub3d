/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:26:09 by emichels          #+#    #+#             */
/*   Updated: 2024/11/20 19:24:43 by emichels         ###   ########.fr       */
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

uint32_t apply_shading(uint32_t color, float shading_factor)
{
	int r;
	int g;
	int b;
	int a;
	
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
	return (r << 24) | (g << 16) | (b << 8) | a;
}


/* static void draw_ceiling(t_map *map, int ray_index, int wall_top)
{
	int	y;

	y = 0;
	while(y < wall_top)
	{
		mlx_put_pixel(map->images->screen, ray_index, y, map->images->color_ceiling);
		y++;
	}
} */

static void draw_walls(t_map *map, int ray_index, int wall_top, int wall_bottom)
{
	int	y;

	y = wall_top;
	while (y < wall_bottom)
	{
		mlx_put_pixel(map->images->screen, ray_index, y, map->images->color_wall);
		y++;
	}
}

/* static void draw_textured_walls(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray, mlx_texture_t *texture)
{
	int y;
	float texture_x;
	float texture_y;
	float texture_step;
	int texel;
	uint32_t color;

	if (texture == NULL) {
		printf("Error: draw_textured_walls: texture is NULL.\n");
		return;
	}

	// Calculate texture X coordinate based on whether it's a vertical or horizontal hit
	if (ray->hit_vertical) {
		// For vertical walls, map texture_x based on the Y coordinate
		texture_x = ray->ray_y - floor(ray->ray_y);
	} else {
		// For horizontal walls, map texture_x based on the X coordinate
		texture_x = ray->ray_x - floor(ray->ray_x);
	}

	// Ensure texture_x is within bounds of texture width
	texture_x *= texture->width;
	if (texture_x < 0) texture_x = 0;
	if (texture_x >= texture->width) texture_x = texture->width - 1;

	// Calculate step size to sample the texture along the height of the wall slice
	texture_step = (float)texture->height / (wall_bottom - wall_top);
	texture_y = 0.0f;

	// Loop through each pixel in the wall slice and draw the corresponding texture pixel
	for (y = wall_top; y < wall_bottom; y++) {
		// Calculate texture Y coordinate
		int texel_y = (int)texture_y % texture->height;

		// Get the current texel (pixel) from the texture
		texel = texel_y * texture->width + (int)texture_x;

		// Fetch the color from the texture
		color = ((uint32_t *)texture->pixels)[texel];

		// Apply shading to the texture color based on distance
		float shading_factor = 1.0f / (ray->distance * 0.5f);
		shading_factor = fmaxf(fminf(shading_factor, 1.0f), 0.2f);  // Clamp to avoid over-darkening or over-brightening
		color = apply_shading(color, shading_factor);

		// Draw the textured pixel
		mlx_put_pixel(map->images->screen, ray_index, y, color);

		// Move to the next pixel in the wall slice
		texture_y += texture_step;
	}
} */




static void draw_floors(t_map *map, int ray_index, int wall_bottom)
{
	int	y;

	y = wall_bottom;
	while (y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(map->images->screen, ray_index, y, map->images->color_floor);
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

static void draw_ray_slice(t_map *map, t_ray *ray, int ray_index)
{
    float	perpendicular_distance;
    int 	wall_height;
	int		wall_top;
	int		wall_bottom;
    float	shading_factor;

    perpendicular_distance = ray->distance * fabs(cos(ray->angle - map->plr_angle));
    if (perpendicular_distance < 0.1f)
        perpendicular_distance = 0.1f;
    wall_height = (int)(SCREEN_HEIGHT / perpendicular_distance);
    wall_top = (SCREEN_HEIGHT / 2) - (wall_height / 2);
    wall_bottom = (SCREEN_HEIGHT / 2) + (wall_height / 2);

    if (wall_top < 0)
        wall_top = 0;
    if (wall_bottom > SCREEN_HEIGHT)
        wall_bottom = SCREEN_HEIGHT;
    shading_factor = 1.0f / (perpendicular_distance * 0.5f);
    shading_factor = fmaxf(fminf(shading_factor, 1.0f), 0.2f);
    if (ray->hit_e == 1 && check_for_textures(map, map->textures->wall_ea) == 0)
        draw_textured_wall_east(map, ray_index, wall_top, wall_bottom, ray);
    else if (ray->hit_w == 1 && check_for_textures(map, map->textures->wall_we) == 0)
        draw_textured_wall_west(map, ray_index, wall_top, wall_bottom, ray);
	else if (ray->hit_s == 1 && check_for_textures(map, map->textures->wall_so) == 0)
        draw_textured_wall_south(map, ray_index, wall_top, wall_bottom, ray);
	else if (ray->hit_n == 1 && check_for_textures(map, map->textures->wall_no) == 0)
        draw_textured_wall_north(map, ray_index, wall_top, wall_bottom, ray);
	else
		draw_walls(map, ray_index, wall_top, wall_bottom);
    //draw_ceiling(map, ray_index, wall_top);
    draw_floors(map, ray_index, wall_bottom);
}


void draw_3d_scene(t_map *map)
{
	int	ray_index;
	t_ray *ray;
	
	ray_index = 0;
	//printf("ceiling color in draw_3d_scene: 0x%08X\n", map->images->color_ceiling);
	//printf("floor color in draw_3d_scene: 0x%08X\n", map->images->color_floor);
	while (ray_index < SCREEN_WIDTH)
	{
		ray = &map->rays[ray_index];
		if (ray->distance > 0)
			draw_ray_slice(map, ray, ray_index);
		ray_index++;
	}
}




