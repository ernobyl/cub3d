/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:16:17 by emichels          #+#    #+#             */
/*   Updated: 2024/10/01 14:21:30 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	safe_img_to_window(t_map *map, mlx_image_t *img)
{
	if (mlx_image_to_window(map->mlx, img, map->x * MINIWIDTH, map->y * MINIHEIGHT) < 0)
		struct_error((char *)mlx_strerror(mlx_errno), map);
}

static void	display_images(t_map *map, int i)
{
	if (map->str[i] == '1')
	{
		safe_img_to_window(map, map->images->mini_w);
	}
	if (map->str[i] == '\n')
	{
		map->y++;
		map->x = 0;
	}
	else
		map->x++;
	// else if (map->str[i] == '0' || map->str[i] == 'P' || map->str[i] == 'C')
	// {
	// 	safe_img_to_window(map, map->images->f_img);
	// 	if (map->str[i] == 'C')
	// 		safe_img_to_window(map, map->images->c_img);
	// 	map->x++;
	// }
	// else if (map->str[i] == 'E')
	// {
	// 	safe_img_to_window(map, map->images->dc_img);
	// 	safe_img_to_window(map, map->images->do_img);
	// 	map->images->do_img->enabled = false;
	// 	map->x++;
	// }
}

// static void	display_player(t_map *map)
// {
// 	map->y = 1;
// 	while (map->y < map->max_y)
// 	{
// 		map->x = 1;
// 		while (map->arr[map->y][map->x])
// 		{
// 			if (map->arr[map->y][map->x] == 'P')
// 			{
// 				map->plr_y = map->y;
// 				map->plr_x = map->x;
// 				safe_img_to_window(map, map->images->p_img);
// 				break ;
// 			}
// 			map->x++;
// 		}
// 		if (map->arr[map->y][map->x] == 'P')
// 			break ;
// 		map->y++;
// 	}
// }

void	display_map(t_map *map)
{
	int	i;

	// load_textures(map);
	// if (!map->images)
	// 	struct_error((char *)mlx_strerror(mlx_errno), map);
	// resize_images(map);
	i = 0;
	map->y = 0;
	map->x = 0;
	while (map->str[i])
	{
		display_images(map, i);
		i++;
	}
	//display_player(map);
}
