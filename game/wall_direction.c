/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/11/26 12:01:15 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	reset_direction(t_ray *ray)
{
	ray->hit_n = 0;
	ray->hit_s = 0;
	ray->hit_e = 0;
	ray->hit_w = 0;
}

void	looking_north(t_map *map, t_ray *ray, float tolerance)
{
	float	x_l;
	float	x_r;
	float	y_n;

	x_l = ray->hit_x - floorf(ray->hit_x);
	x_r = fabs(ray->hit_x - ceilf(ray->hit_x));
	y_n = ray->hit_y - floorf(ray->hit_y);
	if (map->plr_x > ray->hit_x)
	{
		y_n += tolerance;
		if (map->arr[(int)ray->hit_y + 1][(int)ray->hit_x] != '1' && x_l < y_n)
			ray->hit_n = 1;
		else
			ray->hit_w = 1;
	}
	else if (map->plr_x < ray->hit_x)
	{
		y_n += tolerance;
		if (map->arr[(int)ray->hit_y + 1][(int)ray->hit_x] != '1' && x_r < y_n)
			ray->hit_n = 1;
		else
			ray->hit_e = 1;
	}
	else if (map->plr_x == ray->hit_x)
		ray->hit_n = 1;
}

void	looking_south(t_map *map, t_ray *ray, float tolerance)
{
	float	x_l;
	float	x_r;
	float	y_s;

	x_l = ray->hit_x - floorf(ray->hit_x);
	x_r = fabs(ray->hit_x - ceilf(ray->hit_x));
	y_s = fabs(ray->hit_y - ceilf(ray->hit_y));
	if (map->plr_x < ray->hit_x)
	{
		y_s += tolerance;
		if (map->arr[(int)ray->hit_y - 1][(int)ray->hit_x] != '1' && x_r < y_s)
			ray->hit_s = 1;
		else
			ray->hit_e = 1;
	}
	else if (map->plr_x > ray->hit_x)
	{
		y_s += tolerance;
		if (map->arr[(int)ray->hit_y - 1][(int)ray->hit_x] != '1' && x_l < y_s)
			ray->hit_s = 1;
		else
			ray->hit_w = 1;
	}
	else if (map->plr_x == ray->hit_x)
		ray->hit_s = 1;
}

void	check_direction(t_map *map, t_ray *ray)
{
	if (map->plr_y > ray->hit_y)
		looking_north(map, ray, 0.01f);
	else if (map->plr_y < ray->hit_y)
		looking_south(map, ray, 0.01f);
	else if (map->plr_y == ray->hit_y)
	{
		if (map->plr_x < ray->hit_x)
			ray->hit_e = 1;
		else if (map->plr_x > ray->hit_x)
			ray->hit_w = 1;
	}
}

int	check_hit(t_map *map, t_ray *ray)
{
	int	map_x;
	int	map_y;

	if (ray->ray_dir_x < 0)
		map_x = (int)floorf(ray->ray_x - EPSILON);
	else
		map_x = (int)floorf(ray->ray_x + EPSILON);
	if (ray->ray_dir_y < 0)
		map_y = (int)floorf(ray->ray_y - EPSILON);
	else
		map_y = (int)floorf(ray->ray_y + EPSILON);
	reset_direction(ray);
	if (map_x >= 0 && map_x < map->max_x && map_y >= 0 && map_y <= map->max_y)
	{
		if (map->arr[map_y][map_x] == '1'
			|| check_diagonal(map, map_x, map_y, ray))
		{
			ray->hit_x = ray->ray_x;
			ray->hit_y = ray->ray_y;
			ray->hit = 1;
			check_direction(map, ray);
			return (1);
		}
	}
	return (0);
}
