/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:36:11 by msilfver          #+#    #+#             */
/*   Updated: 2024/11/20 23:13:26 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_ray(t_map *map, t_ray *ray, float ray_angle)
{
	ray->ray_x = map->plr_x;
	ray->ray_y = map->plr_y;
	ray->angle = ray_angle;
	ray->distance = 0.0f;
	ray->hit = 0;
	ray->hit_x = 0.0f;
	ray->hit_y = 0.0f;
	ray->ray_dir_x = cos(ray->angle);
	ray->ray_dir_y = sin(ray->angle);
	ray->hit_vertical = 0;
}

static void	update_ray_position(t_ray *ray, float step_size)
{
	ray->ray_x += cos(ray->angle) * step_size;
	ray->ray_y += sin(ray->angle) * step_size;
	ray->distance += step_size;
}

int	check_diagonal(t_map *map, int x, int y, t_ray *ray)
{
	if (x > 0 && y > 0 && ((int)map->plr_x < x)
		&& (map->arr[y][x - 1] == '1')
		&& (map->arr[y - 1][x] == '1')
		&& (map->arr[y - 1][x - 1] == '0')
		&& ray->ray_dir_x > 0 && ray->ray_dir_y > 0)
		return (1);
	if (x < map->max_x - 1 && y > 0 && ((int)map->plr_x > x)
		&& (map->arr[y - 1][x] == '1')
		&& (map->arr[y][x + 1] == '1')
		&& (map->arr[y - 1][x + 1] == '0')
		&& ray->ray_dir_x < 0 && ray->ray_dir_y > 0)
		return (1);
	if (x < map->max_x - 1 && y < map->max_y - 1
		&& ((int)map->plr_x > x)
		&& (map->arr[y + 1][x] == '1')
		&& (map->arr[y][x + 1] == '1')
		&& (map->arr[y + 1][x + 1] == '0')
		&& ray->ray_dir_x < 0 && ray->ray_dir_y < 0)
		return (1);
	if (x > 0 && y < map->max_y - 1 && ((int)map->plr_x < x)
		&& (map->arr[y][x - 1] == '1') && (map->arr[y + 1][x] == '1')
		&& (map->arr[y + 1][x - 1] == '0')
		&& ray->ray_dir_x > 0 && ray->ray_dir_y < 0)
		return (1);
	return (0);
}

void	draw_ray(t_map *map, float ray_angle, int ray_index)
{
	t_ray	*ray;
	float	step_size;
	int		max_distance;

	ray = &map->rays[ray_index];
	step_size = 0.006f;
	max_distance = 64;
	init_ray(map, ray, ray_angle);
	while (!ray->hit && ray->distance < max_distance)
	{
		update_ray_position(ray, step_size);
		if (check_hit(map, ray))
			break ;
	}
}

void	raycasting_rays(t_map *map)
{
	int		num_rays;
	float	fov;
	float	angle_step;
	float	start_angle;
	float	ray_angle;

	num_rays = SCREEN_WIDTH;
	fov = PI / 3;
	angle_step = fov / num_rays;
	start_angle = map->plr_angle - fov / 2;
	map->ray_index = 0;
	while (map->ray_index < num_rays)
	{
		ray_angle = start_angle + map->ray_index * angle_step;
		draw_ray(map, ray_angle, map->ray_index);
		map->ray_index++;
	}
}
