/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:10:33 by emichels          #+#    #+#             */
/*   Updated: 2024/10/24 11:37:52 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	resize_images(t_map *map)
// {
// 	if (mlx_resize_image(map->images->w_img, WIDTH, HEIGHT) == false)
// 		struct_error((char *)mlx_strerror(mlx_errno), map);
// 	if (mlx_resize_image(map->images->f_img, WIDTH, HEIGHT) == false)
// 		struct_error((char *)mlx_strerror(mlx_errno), map);
// 	if (mlx_resize_image(map->images->p_img, WIDTH, HEIGHT) == false)
// 		struct_error((char *)mlx_strerror(mlx_errno), map);
// 	if (mlx_resize_image(map->images->c_img, WIDTH, HEIGHT) == false)
// 		struct_error((char *)mlx_strerror(mlx_errno), map);
// 	if (mlx_resize_image(map->images->dc_img, WIDTH, HEIGHT) == false)
// 		struct_error((char *)mlx_strerror(mlx_errno), map);
// 	if (mlx_resize_image(map->images->do_img, WIDTH, HEIGHT) == false)
// 		struct_error((char *)mlx_strerror(mlx_errno), map);
// }

// void	load_images(t_map *map, t_texture *textures)
// {
// 	map->images = ft_calloc(1, sizeof(t_image));
// 	if (!map->images)
// 		texture_error("Error\nmalloc failed\n", map, textures);
// 	map->images->w_img = mlx_texture_to_image(map->mlx, textures->wall);
// 	if (map->images->w_img == NULL)
// 		texture_error("Error\ntexture to image failed\n", map, textures);
// 	map->images->f_img = mlx_texture_to_image(map->mlx, textures->floor);
// 	if (map->images->f_img == NULL)
// 		texture_error("Error\ntexture to image failed\n", map, textures);
// 	map->images->p_img = mlx_texture_to_image(map->mlx, textures->player);
// 	if (map->images->p_img == NULL)
// 		texture_error("Error\ntexture to image failed\n", map, textures);
// 	map->images->c_img = mlx_texture_to_image(map->mlx, textures->collect);
// 	if (map->images->c_img == NULL)
// 		texture_error("Error\ntexture to image failed\n", map, textures);
// 	map->images->dc_img = mlx_texture_to_image(map->mlx, textures->door_clo);
// 	if (map->images->dc_img == NULL)
// 		texture_error("Error\ntexture to image failed\n", map, textures);
// 	map->images->do_img = mlx_texture_to_image(map->mlx, textures->door_opn);
// 	if (map->images->do_img == NULL)
// 		texture_error("Error\ntexture to image failed\n", map, textures);
// 	free_textures(textures);
// 	free(textures);
// }

void	load_textures(t_map *map, mlx_texture_t **texture, char *path)
{
	*texture = mlx_load_png(path);
	if (*texture == NULL)
		texture_error("Error\ntexture load failed\n", map);
	//load_images(map, textures);
}

