/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:36:11 by msilfver          #+#    #+#             */
/*   Updated: 2024/10/18 11:48:12 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void init_ray(t_map *map, t_ray *ray, float ray_angle)
{
	ray->ray_x = map->plr_x;
	ray->ray_y = map->plr_y;
	ray->angle = ray_angle;
	ray->distance = 0.0f;
	ray->hit = 0;
}

static void update_ray_position(t_ray *ray, float step_size)
{
	ray->ray_x += cos(ray->angle) * step_size;
	ray->ray_y += sin(ray->angle) * step_size;
	ray->distance += step_size;
}

static int check_hit(t_map *map, t_ray *ray)
{
	int map_x = (int)floor(ray->ray_x);
	int map_y = (int)floor(ray->ray_y);

	if (map_x >= 0 && map_x < map->max_x && map_y >= 0 && map_y <= map->max_y)
	{
		if (map->arr[map_y][map_x] == '1')
		{
			ray->hit_x = map_x;
			ray->hit_y = map_y;
			ray->hit = 1;
			return 1;
		}
	}
	return 0;
}

void draw_ray(t_map *map, float ray_angle, int ray_index)
{
	t_ray *ray;
	float step_size;
	int max_distance;
	int pixel_x;
	int	pixel_y;

	ray = &map->rays[ray_index];
	step_size = 0.1f;
	max_distance = 128;
	init_ray(map, ray, ray_angle);
	while (!ray->hit && ray->distance < max_distance)
	{
		update_ray_position(ray, step_size);

		if (check_hit(map, ray)) break;

		pixel_x = (int)((ray->ray_x - map->plr_x) * MINIWIDTH + 128);
		pixel_y = (int)((ray->ray_y - map->plr_y) * MINIHEIGHT + 128);

		if (pixel_x >= 0 && pixel_x < 256 && pixel_y >= 0 && pixel_y < 256)
			mlx_put_pixel(map->images->mini_p, pixel_x, pixel_y, YELLOW);
		else
			break;
	}
}

void raycasting_rays(t_map *map)
{
	int num_rays;
	float fov;
	float angle_step;
	float start_angle;
	int	i;
	float ray_angle;

	num_rays = SCREENWIDTH;
	fov = PI / 2; // 90 degrees, PI / 3 would be 60
	angle_step = fov / num_rays;
	start_angle = map->plr_angle - fov / 2;
	i = 0;
	while (i < num_rays)
	{
		ray_angle = start_angle + i * angle_step;
		draw_ray(map, ray_angle, i);
		i++;
	}
}

