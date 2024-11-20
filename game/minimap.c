/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:39:41 by emichels          #+#    #+#             */
/*   Updated: 2024/11/20 22:47:59 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_wall(t_map	*map, int x, int y)
{
	uint32_t	color;
	int			i;
	int			j;

	color = map->images->color_miniwall;
	i = -1;
	while (++i < MINIWIDTH)
	{
		j = -1;
		while (++j < MINIHEIGHT)
			mlx_put_pixel(map->images->minimap,
				x * MINIWIDTH + i, y * MINIHEIGHT + j, color);
	}
}

void	put_floor(t_map *map, int x, int y)
{
	uint32_t	color;
	int			i;
	int			j;

	color = map->images->color_minifloor;
	i = -1;
	while (++i < MINIWIDTH)
	{
		j = -1;
		while (++j < MINIHEIGHT)
		{
			mlx_put_pixel(map->images->minimap,
				x * MINIWIDTH + i, y * MINIHEIGHT + j, color);
		}
	}
}

void	put_player(t_map *map)
{
	int		offset;

	map->plr_x += 0.5f;
	map->plr_y += 0.5f;
	offset = 256 / 2;
	map->images->mini_p = mlx_new_image(map->mlx, 256, 256);
	map->images->color_player = RED_TP;
	draw_arrow(map, map->plr_angle);
	safe_img_to_window(map, map->images->mini_p,
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
	safe_img_to_window(map, map->images->minimap, 0, 0);
}

void	init_minimap(t_map *map)
{
	map->images->color_miniwall = WHITE_TP;
	map->images->color_minifloor = BLACK_TP;
	map->images->minimap = mlx_new_image(map->mlx, map->max_x
			* MINIWIDTH * 2, map->max_y * MINIHEIGHT * 2);
}
