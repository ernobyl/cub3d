/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:39:41 by emichels          #+#    #+#             */
/*   Updated: 2024/10/09 11:50:12 by emichels         ###   ########.fr       */
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

// void	init_miniplayer(t_map *map)
// {
// 	map->images->mini_p = mlx_new_image(map->mlx, 256, 256);
// 	map->images->color_player = RED;
// }

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

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

void	put_floor(t_map *map, int x, int y)
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

void	put_player(t_map *map)
{
	int	offset;

	map->plr_x += 0.5f;
	map->plr_y += 0.5f;
	offset = 256 / 2;
	map->images->mini_p = mlx_new_image(map->mlx, 256, 256);
	map->images->color_player = RED;
	mlx_put_pixel(map->images->mini_p, 256 / 2, 256 / 2, RED);
	mlx_image_to_window(map->mlx, map->images->mini_p, ((map->plr_x - 0.5f) * MINIWIDTH) + (MINIWIDTH / 2) - offset, ((map->plr_y - 0.5f) * MINIHEIGHT) + (MINIHEIGHT / 2) - offset);
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
	map->images->color_wall = WHITE;
	//map->images->mini_w = mlx_new_image(map->mlx, MINIWIDTH - 1, MINIHEIGHT - 1);
	map->images->color_floor = BLACK;
	//map->images->mini_f = mlx_new_image(map->mlx, MINIWIDTH - 1, MINIHEIGHT - 1);
	map->images->minimap = mlx_new_image(map->mlx, map->max_x * MINIWIDTH * 2, map->max_y * MINIHEIGHT * 2);
}