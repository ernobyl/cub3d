/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:39:41 by emichels          #+#    #+#             */
/*   Updated: 2024/10/01 14:21:45 by emichels         ###   ########.fr       */
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
	map->images->color_player = 0xFFE0;
	map->images->mini_p = mlx_new_image(map->mlx, 8, 8);
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
	
	map = (t_map *)param;
	for (uint32_t i = 0; i < map->images->mini_p->width; ++i)
	{
		for (uint32_t y = 0; y < map->images->mini_p->height; ++y)
		{
			uint32_t color = map->images->color_player;
			mlx_put_pixel(map->images->mini_p, i, y, color);
		}
	}
}

void draw_walls(void* param)
{
	t_map *map;
	
	map = (t_map *)param;
	for (uint32_t i = 0; i < map->images->mini_w->width; ++i)
	{
		for (uint32_t y = 0; y < map->images->mini_w->height; ++y)
		{
			uint32_t color = map->images->color_wall;
			mlx_put_pixel(map->images->mini_w, i, y, color);
		}
	}
}

void	init_minimap(t_map *map)
{
	// map->images = ft_calloc(1, sizeof(t_image));
	// if (!map->images)
	// 	struct_error("Calloc Image failed\n", map);
	map->images->color_wall = 0x07E0;
	map->images->mini_w = mlx_new_image(map->mlx, MINIWIDTH - 1, MINIHEIGHT - 1);
}