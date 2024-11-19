/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:16:08 by msilfver          #+#    #+#             */
/*   Updated: 2024/11/19 15:24:02 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_textured_wall_north(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray)
{
    float texture_x;
    float texture_y_start;
    float texture_step;
    float texture_y;
    uint32_t color;
    mlx_texture_t *texture;
    int texel_y;
    int texel;
    int y;

    texture = map->textures->wall_no;
    if (texture == NULL)
        return;

    // Determine the horizontal position on the texture
    texture_x = ray->ray_x - floor(ray->ray_x);
    texture_x *= texture->width;

    // Adjust texture sampling for vertical stretching
    float perpendicular_distance = ray->distance * fabs(cos(ray->angle - map->plr_angle));
    if (perpendicular_distance < 0.1f)
        perpendicular_distance = 0.1f; // Avoid extreme closeness
    float wall_height = (float)SCREEN_HEIGHT / perpendicular_distance;

    // Start texture_y based on wall's top alignment
    texture_y_start = ((wall_top - (SCREEN_HEIGHT / 2 - wall_height / 2)) * texture->height) / wall_height;

    // Step size adjusts texture_y sampling
    texture_step = (float)texture->height / wall_height;

    texture_y = texture_y_start; // Start texture sampling
    y = wall_top;

    while (y < wall_bottom)
    {
        texel_y = (int)texture_y % texture->height;
        texel = texel_y * texture->width + (int)texture_x;
        color = ((uint32_t *)texture->pixels)[texel];

        // Apply shading based on distance
        color = apply_shading(color, 1.0f / (ray->distance * 0.5f));

        // Draw the pixel on the screen
        mlx_put_pixel(map->images->screen, ray_index, y, color);

        texture_y += texture_step; // Increment texture_y
        y++;
    }
}


void draw_textured_wall_south(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray)
{
    float texture_x;
    float texture_y_start;
    float texture_step;
    float texture_y;
    uint32_t color;
    mlx_texture_t *texture;
    int texel_y;
    int texel;
    int y;

    texture = map->textures->wall_so;
    if (texture == NULL)
        return;

    // Determine the horizontal position on the texture
    texture_x = ray->ray_x - floor(ray->ray_x);
    texture_x *= texture->width;

    // Adjust texture sampling for vertical stretching
    float perpendicular_distance = ray->distance * fabs(cos(ray->angle - map->plr_angle));
    if (perpendicular_distance < 0.1f)
        perpendicular_distance = 0.1f; // Avoid extreme closeness
    float wall_height = (float)SCREEN_HEIGHT / perpendicular_distance;

    // Start texture_y based on wall's top alignment
    texture_y_start = ((wall_top - (SCREEN_HEIGHT / 2 - wall_height / 2)) * texture->height) / wall_height;

    // Step size adjusts texture_y sampling
    texture_step = (float)texture->height / wall_height;

    texture_y = texture_y_start; // Start texture sampling
    y = wall_top;

    while (y < wall_bottom)
    {
        texel_y = (int)texture_y % texture->height;
        texel = texel_y * texture->width + (int)texture_x;
        color = ((uint32_t *)texture->pixels)[texel];

        // Apply shading based on distance
        color = apply_shading(color, 1.0f / (ray->distance * 0.5f));

        // Draw the pixel on the screen
        mlx_put_pixel(map->images->screen, ray_index, y, color);

        texture_y += texture_step; // Increment texture_y
        y++;
    }
}


void draw_textured_wall_east(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray)
{
    float texture_x;
    float texture_y_start;
    float texture_step;
	float texture_y;
    uint32_t color;
    mlx_texture_t *texture;
    int texel_y;
    int texel;
    int y;

    texture = map->textures->wall_ea;
    if (texture == NULL)
        return;

    // Determine the horizontal position on the texture
    texture_x = ray->ray_y - floor(ray->ray_y);
    texture_x *= texture->width;

    // Adjust texture sampling for vertical stretching
    float perpendicular_distance = ray->distance * fabs(cos(ray->angle - map->plr_angle));
    if (perpendicular_distance < 0.1f)
        perpendicular_distance = 0.1f; // Avoid extreme closeness
    float wall_height = (float)SCREEN_HEIGHT / perpendicular_distance;

    // Start texture_y based on wall's top alignment
    texture_y_start = ((wall_top - (SCREEN_HEIGHT / 2 - wall_height / 2)) * texture->height) / wall_height;

    // Step size adjusts texture_y sampling
    texture_step = (float)texture->height / wall_height;

    texture_y = texture_y_start; // Start texture sampling
    y = wall_top;

    while (y < wall_bottom)
    {
        texel_y = (int)texture_y % texture->height;
        texel = texel_y * texture->width + (int)texture_x;
        color = ((uint32_t *)texture->pixels)[texel];

        // Apply shading based on distance
        color = apply_shading(color, 1.0f / (ray->distance * 0.5f));

        // Draw the pixel on the screen
        mlx_put_pixel(map->images->screen, ray_index, y, color);

        texture_y += texture_step; // Increment texture_y
        y++;
    }
}


void draw_textured_wall_west(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray)
{
    float texture_x;
    float texture_y_start;
    float texture_step;
    float texture_y;
    uint32_t color;
    mlx_texture_t *texture;
    int texel_y;
    int texel;
    int y;

    texture = map->textures->wall_we;
    if (texture == NULL)
        return;

    // Determine the horizontal position on the texture
    texture_x = ray->ray_y - floor(ray->ray_y);
    texture_x *= texture->width;

    // Adjust texture sampling for vertical stretching
    float perpendicular_distance = ray->distance * fabs(cos(ray->angle - map->plr_angle));
    if (perpendicular_distance < 0.1f)
        perpendicular_distance = 0.1f; // Avoid extreme closeness
    float wall_height = (float)SCREEN_HEIGHT / perpendicular_distance;

    // Start texture_y based on wall's top alignment
    texture_y_start = ((wall_top - (SCREEN_HEIGHT / 2 - wall_height / 2)) * texture->height) / wall_height;

    // Step size adjusts texture_y sampling
    texture_step = (float)texture->height / wall_height;

    texture_y = texture_y_start; // Start texture sampling
    y = wall_top;

    while (y < wall_bottom)
    {
        texel_y = (int)texture_y % texture->height;
        texel = texel_y * texture->width + (int)texture_x;
        color = ((uint32_t *)texture->pixels)[texel];

        // Apply shading based on distance
        color = apply_shading(color, 1.0f / (ray->distance * 0.5f));

        // Draw the pixel on the screen
        mlx_put_pixel(map->images->screen, ray_index, y, color);

        texture_y += texture_step; // Increment texture_y
        y++;
    }
}







