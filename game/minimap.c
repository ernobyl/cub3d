/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:39:41 by emichels          #+#    #+#             */
/*   Updated: 2024/10/08 18:22:24 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* void	draw_player(void *param)
{
	t_map *map;
	uint32_t	i;
	uint32_t	j;

	i = -1;
	j = -1;
	map = (t_map *)param;
	while (++i < map->images->mini_p->width)
	{
		while (++j < map->images->mini_p->height)
			mlx_put_pixel(map->images->mini_p, i, j, map->images->player);
	}
}  */

void	init_miniplayer(t_map *map)
{
	printf("before calloc\n");
	map->images = ft_calloc(1, sizeof(t_image));
	if (!map->images)
		struct_error("Calloc Image failed\n", map);
	map->images->color_player = 0xFFFF00FF;
	//map->images->mini_p = mlx_new_image(map->mlx, MINIWIDTH, MINIHEIGHT);
	printf("after calloc\n");
	printf("mlx_image_to_window success\n");
}

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

void draw_player(void* param)
{
	t_map *map;
	int	x;
	int	y;

	x = MINIWIDTH / 2;
	y = MINIHEIGHT / 2;
	map = (t_map *)param;
	uint32_t color = map->images->color_player;
	mlx_put_pixel(map->images->mini_p, x, y, color);
}

void	put_wall(t_map	*map, int x, int y)
{
	uint32_t	color;
	
	color = map->images->color_wall;
	for (uint32_t i = 0; i < MINIWIDTH; ++i)
	{
		for (uint32_t j = 0; j < MINIHEIGHT; ++j)
		{
			mlx_put_pixel(map->images->minimap, x * MINIWIDTH + i, y * MINIHEIGHT + j, color);
		}
	}
}

void	put_floor(t_map	*map, int x, int y)
{
	uint32_t	color;
	
	color = map->images->color_floor;
	for (uint32_t i = 0; i < MINIWIDTH; ++i)
	{
		for (uint32_t j = 0; j < MINIHEIGHT; ++j)
		{
			mlx_put_pixel(map->images->minimap, x * MINIWIDTH + i, y * MINIHEIGHT + j, color);
		}
	}
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
			x++;
		}
		y++;
	}
	mlx_image_to_window(map->mlx, map->images->minimap, 0, 0);
}

void	draw_floor(void* param)
{
	t_map *map;
	
	map = (t_map *)param;
	for (uint32_t i = 0; i < map->images->mini_f->width; ++i)
	{
		for (uint32_t y = 0; y < map->images->mini_f->height; ++y)
		{
			uint32_t color = map->images->color_floor;
			mlx_put_pixel(map->images->mini_f, i, y, color);
		}
	}
}

void	init_minimap(t_map *map)
{
	map->images = ft_calloc(1, sizeof(t_image));
	// if (!map->images)
	// 	struct_error("Calloc Image failed\n", map);
	map->images->color_wall = 0xFFFFFFFF;
	//map->images->mini_w = mlx_new_image(map->mlx, MINIWIDTH - 1, MINIHEIGHT - 1);
	map->images->color_floor = 0x000000FF;
	//map->images->mini_f = mlx_new_image(map->mlx, MINIWIDTH - 1, MINIHEIGHT - 1);
	map->images->minimap = mlx_new_image(map->mlx, map->max_x * MINIWIDTH * 2, map->max_y * MINIHEIGHT * 2);
}