/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:54:24 by emichels          #+#    #+#             */
/*   Updated: 2024/11/20 19:18:49 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pov_object.h"

static void	init_sprites(t_map *map)
{
	map->sprites->sprite_frame_1 = mlx_load_png("./sprites/frame1.png");
	// if (map->sprites->sprite_frame_1 == NULL) handle errors
	map->sprites->sprite_frame_2 = mlx_load_png("./sprites/frame2.png");
	map->sprites->sprite_frame_3 = mlx_load_png("./sprites/frame3.png");
	map->sprites->pov_frame1 = mlx_texture_to_image(map->mlx, map->sprites->sprite_frame_1);
	// handle errors
	map->sprites->pov_frame2 = mlx_texture_to_image(map->mlx, map->sprites->sprite_frame_2);
	map->sprites->pov_frame3 = mlx_texture_to_image(map->mlx, map->sprites->sprite_frame_3);
	mlx_resize_image(map->sprites->pov_frame1, 128, 128);
	mlx_resize_image(map->sprites->pov_frame2, 128, 128);
	mlx_resize_image(map->sprites->pov_frame3, 128, 128);
	mlx_delete_texture(map->sprites->sprite_frame_1);
	mlx_delete_texture(map->sprites->sprite_frame_2);
	mlx_delete_texture(map->sprites->sprite_frame_3);
	map->sprites->pov_frame1->enabled = 1;
	map->sprites->pov_frame2->enabled = 0;
	map->sprites->pov_frame3->enabled = 0;
}

void	create_pov_object(t_map *map)
{
	int	center_x;
	int	center_y;
	
	map->sprites = ft_calloc(1, sizeof(t_pov));
	init_sprites(map);
	center_x = (SCREEN_WIDTH / 2) - 64;
	center_y = SCREEN_HEIGHT - 128;
	safe_img_to_window(map, map->sprites->pov_frame1, center_x, center_y);
	safe_img_to_window(map, map->sprites->pov_frame2, center_x, center_y);
	safe_img_to_window(map, map->sprites->pov_frame3, center_x, center_y);
}

static int	frame_status(t_map *map)
{
	if (map->sprites->pov_frame1->enabled == 1
		&& map->sprites->pov_frame2->enabled == 0
		&& map->sprites->pov_frame3->enabled == 0)
		return (1);
	if (map->sprites->pov_frame1->enabled == 0
		&& map->sprites->pov_frame2->enabled == 1
		&& map->sprites->pov_frame3->enabled == 0)
		return (2);
	if (map->sprites->pov_frame1->enabled == 0
		&& map->sprites->pov_frame2->enabled == 0
		&& map->sprites->pov_frame3->enabled == 1)
		return (3);
	else
		return (0);
}

void	animate_pov_obj(t_map *map)
{
	int	status;
	
	status = frame_status(map);
	if (status == 1)
	{
		map->sprites->pov_frame1->enabled = false;
		map->sprites->pov_frame2->enabled = true;
		map->sprites->pov_frame3->enabled = false;
	}
	else if (status == 2)
	{
		map->sprites->pov_frame1->enabled = false;
		map->sprites->pov_frame2->enabled = false;
		map->sprites->pov_frame3->enabled = true;
	}
	else if (status == 3)
	{
		map->sprites->pov_frame1->enabled = true;
		map->sprites->pov_frame2->enabled = false;
		map->sprites->pov_frame3->enabled = false;
	}
}
