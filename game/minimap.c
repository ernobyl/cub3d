/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:39:41 by emichels          #+#    #+#             */
/*   Updated: 2024/10/22 13:09:46 by emichels         ###   ########.fr       */
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
		mlx_put_pixel(map->images->mini_p, x0, y0, RED);
		if (x0 == x1 && y0 == y1)
			break;
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

void	draw_arrow(t_map *map, float angle)
{
	int		length;
	int		width;
	t_tri	tri;

	init_triangle(&tri);
	length = 10;
	width = 5;
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