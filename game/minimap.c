/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:39:41 by emichels          #+#    #+#             */
/*   Updated: 2024/10/17 17:06:39 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_wall(t_map	*map, int x, int y)
{
	uint32_t	color;
	
	color = map->images->color_miniwall;
	for (uint32_t i = 0; i < MINIWIDTH; ++i)
	{
		for (uint32_t j = 0; j < MINIHEIGHT; ++j)
		{
			mlx_put_pixel(map->images->minimap, x * MINIWIDTH + i, y * MINIHEIGHT + j, color);
		}
	}
}

void	put_floor(t_map *map, int x, int y)
{
	uint32_t	color;
	
	color = map->images->color_minifloor;
	for (uint32_t i = 0; i < MINIWIDTH; ++i)
	{
		for (uint32_t j = 0; j < MINIHEIGHT; ++j)
		{
			mlx_put_pixel(map->images->minimap, x * MINIWIDTH + i, y * MINIHEIGHT + j, color);
		}
	}
}

void	draw_line(t_map *map, int x0, int y0, int x1, int y1)
{
	int	dx = abs(x1 - x0);
	int	dy = abs(y1 - y0);
	int	sx = (x0 < x1) ? 1 : -1;
	int	sy = (y0 < y1) ? 1 : -1;
	int	err = dx - dy;
	int	err2;

	while (1)
	{
		// Draw the pixel at the current position
		mlx_put_pixel(map->images->mini_p, x0, y0, RED);

		// Check if we've reached the end of the line
		if (x0 == x1 && y0 == y1)
			break;

		// Update error and adjust x and y accordingly
		err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	init_triangle(t_tri *tri)
{
	tri->tip_x = 0;
	tri->tip_y = 0;
	tri->base_left_x = 0;
	tri->base_left_y = 0;
	tri->base_right_x = 0;
	tri->base_right_y = 0;
	tri->center_x = 256 / 2;
	tri ->center_y = 256 / 2;
}

void raycasting_rays(t_map *map)
{
    int num_rays;
    float fov;
    float angle_step;
    float start_angle;
	int	i;
	float ray_angle;

	num_rays = 30;
	fov = PI / 3;
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

void	draw_arrow(t_map *map, float angle)
{
	int		length;
	int		width;
	t_tri	tri;

	init_triangle(&tri);
	length = 6;
	width = 3;
	// arrow tip
	tri.tip_x = tri.center_x + (int)(cos(angle) * length);
	tri.tip_y = tri.center_y + (int)(sin(angle) * length);

	// arrow base points
	tri.base_left_x = tri.center_x + (int)(cos(angle + (PI / 2)) * width / 2);
	tri.base_left_y = tri.center_y + (int)(sin(angle + (PI / 2)) * width / 2);
	tri.base_right_x = tri.center_x + (int)(cos(angle - (PI / 2)) * width / 2);
	tri.base_right_y = tri.center_y + (int)(sin(angle - (PI / 2)) * width / 2);

	// draw arrow
	draw_line(map, tri.base_left_x, tri.base_left_y, tri.tip_x, tri.tip_y);
	draw_line(map, tri.base_right_x, tri.base_right_y, tri.tip_x, tri.tip_y);
	draw_line(map, tri.base_left_x, tri.base_left_y, tri.base_right_x, tri.base_right_y);
	raycasting_rays(map);
}

void draw_ray(t_map *map, float ray_angle, int ray_index)
{
	float ray_x;
	float ray_y;
	float step_size;
	int hit;
	float ray_distance;
	int max_distance;
	int pixel_x; 
	int pixel_y;
	int map_x;
	int map_y;

	ray_x = map->plr_x;
	ray_y = map->plr_y;
	step_size = 0.1f;
	hit = 0;
	ray_distance = 0.0f;
	max_distance = 128;
	map->rays[ray_index].angle = ray_angle;
	while (!hit && ray_distance < max_distance)
	{
		ray_x += cos(ray_angle) * step_size;
		ray_y += sin(ray_angle) * step_size;
		ray_distance += step_size;
		map_x = (int)floor(ray_x);
		map_y = (int)floor(ray_y);
		if (map_x >= 0 && map_x < map->max_x && map_y >= 0 && map_y <= map->max_y)
		{
			if (map->arr[map_y][map_x] == '1')
			{
				hit = 1;
				map->rays[ray_index].hit_x = map_x;
				map->rays[ray_index].hit_y = map_y;
				map->rays[ray_index].distance = ray_distance;
			}
		}
		pixel_x = (int)((ray_x - map->plr_x) * MINIWIDTH + 128);
		pixel_y = (int)((ray_y - map->plr_y) * MINIHEIGHT + 128);
		if (pixel_x >= 0 && pixel_x < 256 && pixel_y >= 0 && pixel_y < 256)
			mlx_put_pixel(map->images->mini_p, pixel_x, pixel_y, YELLOW);
		else
			break;
	}
}



void	put_player(t_map *map)
{
	int		offset;

	map->plr_x += 0.5f;
	map->plr_y += 0.5f;
	offset = 256 / 2;
	map->images->mini_p = mlx_new_image(map->mlx, 256, 256);
	map->images->color_player = RED;
	draw_arrow(map, map->plr_angle);
	mlx_image_to_window(map->mlx, map->images->mini_p,
		((map->plr_x - 0.5f) * MINIWIDTH) + (MINIWIDTH / 2) - offset,
		((map->plr_y - 0.5f) * MINIHEIGHT) + (MINIHEIGHT / 2) - offset);
}

void	draw_minimap(void *param)
{
	t_map		*map;
	int			x;
	int			y;

	map = (t_map *)param;
	y = 0;
	while (y <= map->max_y)
	{
		x = 0;
		while (map->arr[y] && x < (int)ft_strlen(map->arr[y]))
		{
			if (map->arr[y][x] == '1')
				put_wall(map, x, y);
			if (map->arr[y][x] == '0')
				put_floor(map, x, y);
			if (map->arr[y][x] == 'N' || map->arr[y][x] == 'S'
				|| map->arr[y][x] == 'E' || map->arr[y][x] == 'W')
				put_floor(map, x, y);
			x++;
		}
		y++;
	}
	mlx_image_to_window(map->mlx, map->images->minimap, 0, 0);
}

void	init_minimap(t_map *map)
{
	map->images = ft_calloc(1, sizeof(t_image));
	// if (!map->images)
	// 	struct_error("Calloc Image failed\n", map);
	map->images->color_miniwall = WHITE;
	//map->images->mini_w = mlx_new_image(map->mlx, MINIWIDTH - 1, MINIHEIGHT - 1);
	map->images->color_minifloor = BLACK;
	//map->images->mini_f = mlx_new_image(map->mlx, MINIWIDTH - 1, MINIHEIGHT - 1);
	map->images->minimap = mlx_new_image(map->mlx, map->max_x * MINIWIDTH * 2, map->max_y * MINIHEIGHT * 2);
}