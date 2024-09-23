/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:10:33 by emichels          #+#    #+#             */
/*   Updated: 2024/04/17 15:43:46 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	resize_images(t_map *map)
{
	if (mlx_resize_image(map->images->w_img, WIDTH, HEIGHT) == false)
		struct_error((char *)mlx_strerror(mlx_errno), map);
	if (mlx_resize_image(map->images->f_img, WIDTH, HEIGHT) == false)
		struct_error((char *)mlx_strerror(mlx_errno), map);
	if (mlx_resize_image(map->images->p_img, WIDTH, HEIGHT) == false)
		struct_error((char *)mlx_strerror(mlx_errno), map);
	if (mlx_resize_image(map->images->c_img, WIDTH, HEIGHT) == false)
		struct_error((char *)mlx_strerror(mlx_errno), map);
	if (mlx_resize_image(map->images->dc_img, WIDTH, HEIGHT) == false)
		struct_error((char *)mlx_strerror(mlx_errno), map);
	if (mlx_resize_image(map->images->do_img, WIDTH, HEIGHT) == false)
		struct_error((char *)mlx_strerror(mlx_errno), map);
}

void	load_textures(t_map *map)
{
	t_texture	*textures;

	textures = ft_calloc(1, sizeof(t_texture));
	if (!textures)
		struct_error("Error\nmalloc failed\n", map);
	textures->wall = mlx_load_png("./textures/wall.png");
	if (textures->wall == NULL)
		texture_error("Error\ntexture load failed\n", map, textures);
	textures->floor = mlx_load_png("./textures/floor.png");
	if (textures->floor == NULL)
		texture_error("Error\ntexture load failed\n", map, textures);
	textures->player = mlx_load_png("./textures/player.png");
	if (textures->player == NULL)
		texture_error("Error\ntexture load failed\n", map, textures);
	textures->collect = mlx_load_png("./textures/collect.png");
	if (textures->collect == NULL)
		texture_error("Error\ntexture load failed\n", map, textures);
	textures->door_clo = mlx_load_png("./textures/door_closed.png");
	if (textures->door_clo == NULL)
		texture_error("Error\ntexture load failed\n", map, textures);
	textures->door_opn = mlx_load_png("./textures/door_open.png");
	if (textures->door_opn == NULL)
		texture_error("Error\ntexture load failed\n", map, textures);
	load_images(map, textures);
}

void	load_images(t_map *map, t_texture *textures)
{
	map->images = ft_calloc(1, sizeof(t_image));
	if (!map->images)
		texture_error("Error\nmalloc failed\n", map, textures);
	map->images->w_img = mlx_texture_to_image(map->mlx, textures->wall);
	if (map->images->w_img == NULL)
		texture_error("Error\ntexture to image failed\n", map, textures);
	map->images->f_img = mlx_texture_to_image(map->mlx, textures->floor);
	if (map->images->f_img == NULL)
		texture_error("Error\ntexture to image failed\n", map, textures);
	map->images->p_img = mlx_texture_to_image(map->mlx, textures->player);
	if (map->images->p_img == NULL)
		texture_error("Error\ntexture to image failed\n", map, textures);
	map->images->c_img = mlx_texture_to_image(map->mlx, textures->collect);
	if (map->images->c_img == NULL)
		texture_error("Error\ntexture to image failed\n", map, textures);
	map->images->dc_img = mlx_texture_to_image(map->mlx, textures->door_clo);
	if (map->images->dc_img == NULL)
		texture_error("Error\ntexture to image failed\n", map, textures);
	map->images->do_img = mlx_texture_to_image(map->mlx, textures->door_opn);
	if (map->images->do_img == NULL)
		texture_error("Error\ntexture to image failed\n", map, textures);
	free_textures(textures);
	free(textures);
}
