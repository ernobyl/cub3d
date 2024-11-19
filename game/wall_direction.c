/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:18:45 by emichels          #+#    #+#             */
/*   Updated: 2024/11/19 15:11:38 by emichels         ###   ########.fr       */
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
	float	x_scan_l;
	float	x_scan_r;
	float	y_scan_no;

	x_scan_l = ray->hit_x - floorf(ray->hit_x);
	x_scan_r = fabs(ray->hit_x - ceilf(ray->hit_x));
	y_scan_no = ray->hit_y - floorf(ray->hit_y);
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

void	looking_south(t_map *map, t_ray *ray, float tolerance)
{
	float	x_scan_l;
	float	x_scan_r;
	float	y_scan_so;

	x_scan_l = ray->hit_x - floorf(ray->hit_x);
	x_scan_r = fabs(ray->hit_x - ceilf(ray->hit_x));
	y_scan_so = fabs(ray->hit_y - ceilf(ray->hit_y));
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
			y_scan_so += tolerance;
			if (map->arr[(int)ray->hit_y - 1][(int)ray->hit_x] != '1' && x_scan_l < y_scan_so)
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
