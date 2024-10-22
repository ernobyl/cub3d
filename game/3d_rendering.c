/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:26:09 by emichels          #+#    #+#             */
/*   Updated: 2024/10/22 15:21:40 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_3d_screen(t_map *map)
{
	map->images->screen = mlx_new_image(map->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(map->mlx, map->images->screen, 320, 240);
}

void cast_ray(t_map *map, int ray_index, float ray_angle)
{
	t_ray *ray = &map->rays[ray_index];  // Access the specific ray in the array
	ray->ray_x = map->plr_x;
	ray->ray_y = map->plr_y;
	float step_size = 0.05f;
	ray->distance = 0.0f;
	ray->hit = 0;

	while (!ray->hit && ray->distance < MAX_RENDER_DISTANCE)
	{
		ray->ray_x += cos(ray_angle) * step_size;
		ray->ray_y += sin(ray_angle) * step_size;
		ray->distance += step_size;

		int map_x = (int)ray->ray_x;
		int map_y = (int)ray->ray_y;

		if (map_x >= 0 && map_x < map->max_x && map_y >= 0 && map_y < map->max_y)
		{
			if (map->arr[map_y][map_x] == '1')
			{
				ray->hit = 1;
			}
		}
		else
		{
			break;
		}
	}
	// Store the perpendicular distance to avoid fisheye effect
	ray->distance *= cos(ray_angle - map->plr_angle);
}


uint32_t apply_shading(uint32_t color, float shading_factor)
{
	// Extract RGBA components from the color
	int r = (color >> 24) & 0xFF;
	int g = (color >> 16) & 0xFF;
	int b = (color >> 8) & 0xFF;
	int a = color & 0xFF;

	// Apply shading factor
	r = (int)(r * shading_factor);
	g = (int)(g * shading_factor);
	b = (int)(b * shading_factor);

	// Reconstruct color with shaded values
	return (r << 24) | (g << 16) | (b << 8) | a;
}

void draw_3d_scene(t_map *map)
{   
	float perpendicular_distance;
	int wall_height;
	int wall_top;
	int wall_bottom;
	float shading_factor;
	uint32_t wall_color;
	int y;
	int ray_index;
	
	ray_index = 0;
	while (ray_index < SCREEN_WIDTH)
	{
		t_ray *ray;
		
		ray = &map->rays[ray_index];
		if (ray->distance <= 0)
			continue;
		perpendicular_distance = ray->distance * cos(ray->angle - map->plr_angle); // to avoid fisheye
		if (perpendicular_distance < 0.1f)
			perpendicular_distance = 0.1f;
		wall_height = (int)(SCREEN_HEIGHT / perpendicular_distance);
		wall_top = (SCREEN_HEIGHT / 2) - (wall_height / 2); // Define where the wall starts and ends on the screen
		wall_bottom = (SCREEN_HEIGHT / 2) + (wall_height / 2); // ...
		if (wall_top < 0) // Ensure no out-of-bounds screen rendering
			wall_top = 0;
		if (wall_bottom > SCREEN_HEIGHT)
			wall_bottom = SCREEN_HEIGHT;
		shading_factor = 1.0f / (perpendicular_distance * 0.5f); // Apply shading based on distance to the wall
		if (shading_factor > 1.0f)
			shading_factor = 1.0f;
		if (shading_factor < 0.2f)
			shading_factor = 0.2f;
		wall_color = apply_shading(RED, shading_factor);
		y = 0;
		while (y < wall_top) // Draw ceiling (above the wall)
		{
			mlx_put_pixel(map->images->screen, ray_index, y, BLUE);
			y++;
		}
		y = wall_top;
		while (y < wall_bottom) // Draw the wall slice with shading
		{
			mlx_put_pixel(map->images->screen, ray_index, y, wall_color);
			y++;
		}
		y = wall_bottom;
		while (y < SCREEN_HEIGHT) // Draw the floor (below the wall)
		{
			mlx_put_pixel(map->images->screen, ray_index, y, GREEN);
			y++;
		}
		ray_index++;
	}
}



