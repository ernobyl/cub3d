/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:07:47 by emichels          #+#    #+#             */
/*   Updated: 2024/11/27 14:41:53 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_images(t_map *map)
{
	if (map->images->mini_p)
		mlx_delete_image(map->mlx, map->images->mini_p);
	if (map->images->minimap)
		mlx_delete_image(map->mlx, map->images->minimap);
	if (map->images->screen)
		mlx_delete_image(map->mlx, map->images->screen);
	free(map->images);
	if (map->sprites)
	{
		if (map->sprites->pov_frame1)
			mlx_delete_image(map->mlx, map->sprites->pov_frame1);
		if (map->sprites->pov_frame2)
			mlx_delete_image(map->mlx, map->sprites->pov_frame2);
		if (map->sprites->pov_frame3)
			mlx_delete_image(map->mlx, map->sprites->pov_frame3);
		free(map->sprites);
	}
}

void	free_textures(t_map *map)
{
	if (map->textures->wall_no)
		mlx_delete_texture(map->textures->wall_no);
	if (map->textures->wall_so)
		mlx_delete_texture(map->textures->wall_so);
	if (map->textures->wall_we)
		mlx_delete_texture(map->textures->wall_we);
	if (map->textures->wall_ea)
		mlx_delete_texture(map->textures->wall_ea);
	free(map->textures);
}

void	free_sprites(t_map *map)
{
	if (map->sprites->sprite_frame_1)
		mlx_delete_texture(map->sprites->sprite_frame_1);
	if (map->sprites->sprite_frame_2)
		mlx_delete_texture(map->sprites->sprite_frame_2);
	if (map->sprites->sprite_frame_3)
		mlx_delete_texture(map->sprites->sprite_frame_3);
}
