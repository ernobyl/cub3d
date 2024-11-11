/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:36:11 by msilfver          #+#    #+#             */
/*   Updated: 2024/11/11 18:23:22 by emichels         ###   ########.fr       */
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
	ray->hit_x = 0.0f;
	ray->hit_y = 0.0f;
	ray->ray_dir_x = cos(ray->angle);
	ray->ray_dir_y = sin(ray->angle);
	ray->hit_vertical = 0;
}

static void update_ray_position(t_ray *ray, float step_size)
{
	ray->ray_x += cos(ray->angle) * step_size;
	ray->ray_y += sin(ray->angle) * step_size;
	ray->distance += step_size;
}

static int check_diagonal(t_map *map, int map_x, int map_y, t_ray *ray)
{
	// Down Right
	if (map_x > 0 && map_y > 0 && ((int)map->plr_x < map_x) &&
		(map->arr[map_y][map_x - 1] == '1') && (map->arr[map_y - 1][map_x] == '1') &&
		(map->arr[map_y - 1][map_x - 1] == '0') && ray->ray_dir_x > 0 && ray->ray_dir_y > 0)
		return (1);
	// Down Left
	if (map_x < map->max_x - 1 && map_y > 0 && ((int)map->plr_x > map_x) &&
		(map->arr[map_y - 1][map_x] == '1') && (map->arr[map_y][map_x + 1] == '1') &&
		(map->arr[map_y - 1][map_x + 1] == '0') && ray->ray_dir_x < 0 && ray->ray_dir_y > 0)
		return (1);
	// Up Left
	if (map_x < map->max_x - 1 && map_y < map->max_y - 1 && ((int)map->plr_x > map_x) &&
		(map->arr[map_y + 1][map_x] == '1') && (map->arr[map_y][map_x + 1] == '1') &&
		(map->arr[map_y + 1][map_x + 1] == '0') && ray->ray_dir_x < 0 && ray->ray_dir_y < 0)
		return (1);
	// Up Right
	if (map_x > 0 && map_y < map->max_y - 1 && ((int)map->plr_x < map_x) &&
		(map->arr[map_y][map_x - 1] == '1') && (map->arr[map_y + 1][map_x] == '1') &&
		(map->arr[map_y + 1][map_x - 1] == '0') && ray->ray_dir_x > 0 && ray->ray_dir_y < 0)
		return (1);
	return (0);
}
void	reset_direction(t_ray *ray)
{
	ray->hit_n = 0;
	ray->hit_s = 0;
	ray->hit_e = 0;
	ray->hit_w = 0;
}

void	check_direction(t_map *map, t_ray *ray)
{
	float	x_scan_l;
	float	x_scan_r;
	float	y_scan_no;
	float	y_scan_so;
	float	tolerance;

	tolerance = 0.005f;
	x_scan_l = ray->hit_x - floorf(ray->hit_x);
	x_scan_r = fabs(ray->hit_x - ceilf(ray->hit_x));
	y_scan_no = ray->hit_y - floorf(ray->hit_y);
	y_scan_so = fabs(ray->hit_y - ceilf(ray->hit_y));
	if (map->plr_y > ray->hit_y)
	{
		if (map->plr_x > ray->hit_x)
		{
			y_scan_no += tolerance;
			if (map->arr[(int)ray->hit_y + 1][(int)ray->hit_x] != '1' && x_scan_l < y_scan_no)
				ray->hit_n = 1;
			else
				ray->hit_w = 1;
		}
		else if (map->plr_x < ray->hit_x)
		{
			y_scan_no += tolerance;
			if (map->arr[(int)ray->hit_y + 1][(int)ray->hit_x] != '1' && x_scan_r < y_scan_no)
				ray->hit_n = 1;
			else
				ray->hit_e = 1;
		}
		else if (map->plr_x == ray->hit_x)
		 	ray->hit_n = 1;
	}
	else if (map->plr_y < ray->hit_y)
	{
		if (map->plr_x < ray->hit_x)
		{
			y_scan_so += tolerance;
			if (map->arr[(int)ray->hit_y - 1][(int)ray->hit_x] != '1' && x_scan_r < y_scan_so)
				ray->hit_s = 1;
			else
				ray->hit_e = 1;
		}
		else if (map->plr_x > ray->hit_x)
		{
			y_scan_no += tolerance;
			if (map->arr[(int)ray->hit_y - 1][(int)ray->hit_x] != '1' && x_scan_l < y_scan_so)
				ray->hit_s = 1;
			else
				ray->hit_w = 1;
		}
		else if (map->plr_x == ray->hit_x)
			ray->hit_s = 1;
	}
	else if (map->plr_y == ray->hit_y)
	{
		if (map->plr_x < ray->hit_x)
			ray->hit_e = 1;
		else if (map->plr_x > ray->hit_x)
			ray->hit_w = 1;
	}
}

static int check_hit(t_map *map, t_ray *ray)
{
	int map_x;
	int map_y;

	map_x = (int)floor(ray->ray_x);
	map_y = (int)floor(ray->ray_y);
	reset_direction(ray);
	if (map_x >= 0 && map_x < map->max_x && map_y >= 0 && map_y <= map->max_y)
	{
		if (map->arr[map_y][map_x] == '1' || check_diagonal(map, map_x, map_y, ray))
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

void draw_ray(t_map *map, float ray_angle, int ray_index)
{
	t_ray *ray;
	float step_size;
	int max_distance;
	// int pixel_x;
	// int	pixel_y;

	ray = &map->rays[ray_index];
	step_size = 0.004f;
	max_distance = 64;
	init_ray(map, ray, ray_angle);
	while (!ray->hit && ray->distance < max_distance)
	{
		update_ray_position(ray, step_size);
		if (check_hit(map, ray))
			break;
		// pixel_x = (int)((ray->ray_x - map->plr_x) * MINIWIDTH + 128);
		// pixel_y = (int)((ray->ray_y - map->plr_y) * MINIHEIGHT + 128);
		// if (pixel_x >= 0 && pixel_x < 256 && pixel_y >= 0 && pixel_y < 256)
		// 	mlx_put_pixel(map->images->mini_p, pixel_x, pixel_y, YELLOW_TP);
		// else
		// 	break;
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
	//float prev_distance;

	num_rays = SCREEN_WIDTH;
	//prev_distance = 0.0f;
	fov = PI / 3; // PI / 3 would be 60 deg, PI / 2 is 90 deg
	angle_step = fov / num_rays;
	start_angle = map->plr_angle - fov / 2;
	i = 0;
	while (i < num_rays)
	{
		// if (i > 0)
		// 	map->rays->prev_distance = prev_distance;
		ray_angle = start_angle + i * angle_step;
		draw_ray(map, ray_angle, i);
		//prev_distance = map->rays->distance;
		i++;
	}
}

