/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_rendering.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:26:09 by emichels          #+#    #+#             */
/*   Updated: 2024/10/22 13:58:39 by emichels         ###   ########.fr       */
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

void	draw_3d_scene(t_map *map)
{
    for (int ray_index = 0; ray_index < SCREEN_WIDTH; ray_index++)
    {
        // Calculate the current ray's angle based on the player's direction and field of view
        float ray_angle = map->plr_angle + (ray_index - SCREEN_WIDTH / 2) * (FOV / SCREEN_WIDTH);
        
        // Cast the ray and get the distance to the first wall hit
        float perpendicular_distance = cast_ray(map, ray_angle);

        // Avoid division by zero or small values causing large wall heights
        if (perpendicular_distance <= 0.1)
            perpendicular_distance = 0.1;

        // Calculate the height of the wall slice to draw based on distance
        int wall_height = (int)(SCREEN_HEIGHT / perpendicular_distance);

        // Calculate where the top and bottom of the wall slice should be drawn
        int wall_top = (SCREEN_HEIGHT / 2) - (wall_height / 2);
        int wall_bottom = (SCREEN_HEIGHT / 2) + (wall_height / 2);

        // Render ceiling above the wall
        for (int y = 0; y < wall_top; y++)
            mlx_put_pixel(map->images->screen, ray_index, y, BLUE);

        // Render the wall slice
        for (int y = wall_top; y < wall_bottom; y++)
            mlx_put_pixel(map->images->screen, ray_index, y, RED);

        // Render floor below the wall
        for (int y = wall_bottom; y < SCREEN_HEIGHT; y++)
            mlx_put_pixel(map->images->screen, ray_index, y, GREEN);
    }
}
