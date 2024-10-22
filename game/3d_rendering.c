/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:26:09 by emichels          #+#    #+#             */
/*   Updated: 2024/10/22 14:23:24 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_3d_screen(t_map *map)
{
	map->images->screen = mlx_new_image(map->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(map->mlx, map->images->screen, 320, 240);
}

float	cast_ray(t_map *map, float ray_angle)
{
    float ray_x = map->plr_x;
    float ray_y = map->plr_y;
    float step_size = 0.05; // Small steps to move the ray forward
    float ray_distance = 0.0;
    int hit = 0;
    
    while (!hit && ray_distance < MAX_RENDER_DISTANCE)
    {
        ray_x += cos(ray_angle) * step_size;
        ray_y += sin(ray_angle) * step_size;
        ray_distance += step_size;
        
        // Convert ray coordinates to map grid coordinates
        int map_x = (int)ray_x;
        int map_y = (int)ray_y;

        // Check for collision with a wall ('1' in the map array)
        if (map_x >= 0 && map_x < map->max_x && map_y >= 0 && map_y < map->max_y)
        {
            if (map->arr[map_y][map_x] == '1')
            {
                hit = 1;
            }
        }
        else
        {
            // If the ray goes out of bounds, stop it
            break;
        }
    }

    // Return the distance to the wall (corrected for the fisheye effect)
    return ray_distance * cos(ray_angle - map->plr_angle);
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
    for (int ray_index = 0; ray_index < SCREEN_WIDTH; ray_index++)
    {
        float ray_angle = map->plr_angle + (ray_index - SCREEN_WIDTH / 2) * (FOV / SCREEN_WIDTH);
        
        // Cast the ray and get distance to the wall
        float perpendicular_distance = cast_ray(map, ray_angle);

        // Avoid division by zero
        if (perpendicular_distance < 0.1f)
            perpendicular_distance = 0.1f;

        // Calculate wall height based on distance
        int wall_height = (int)(SCREEN_HEIGHT / perpendicular_distance);

        // Determine where to draw the wall slice on screen
        int wall_top = (SCREEN_HEIGHT / 2) - (wall_height / 2);
        int wall_bottom = (SCREEN_HEIGHT / 2) + (wall_height / 2);

        // Calculate a shading factor based on the distance
        float shading_factor = 1.0f / (perpendicular_distance * 0.5f);  // tune the 0.1 to adjust the shading intensity
        if (shading_factor > 1.0f) shading_factor = 1.0f;  // clamp to avoid over-brightening
        if (shading_factor < 0.2f) shading_factor = 0.2f;  // prevent total darkness

        // Calculate color with shading
        uint32_t wall_color = apply_shading(RED, shading_factor);

        // Render ceiling (just black or other color)
        for (int y = 0; y < wall_top; y++)
            mlx_put_pixel(map->images->screen, ray_index, y, BLUE);

        // Render wall slice with shading
        for (int y = wall_top; y < wall_bottom; y++)
            mlx_put_pixel(map->images->screen, ray_index, y, wall_color);

        // Render floor (just a constant color for now)
        for (int y = wall_bottom; y < SCREEN_HEIGHT; y++)
            mlx_put_pixel(map->images->screen, ray_index, y, GREEN);
    }
}
