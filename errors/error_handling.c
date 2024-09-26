/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:23:58 by emichels          #+#    #+#             */
/*   Updated: 2024/09/26 11:47:13 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	free_textures(t_texture *textures)
// {
// 	mlx_delete_texture(textures->wall);
// 	mlx_delete_texture(textures->floor);
// }

static void	debug_map(t_map *map)
{
	printf("Invalid map element at x: %i y: %i\n", map->x + 1, map->y + 1);
}

void	free_images(t_map *map)
{
	if (map->images->w_img)
		mlx_delete_image(map->mlx, map->images->w_img);
	if (map->images->f_img)
		mlx_delete_image(map->mlx, map->images->f_img);
	free(map->images);
}

void	struct_error(char *msg, t_map *map)
{
	if (ft_strcmp(msg, "Error\nmap not walled\n") == 0)
		debug_map(map);
	if (map->str)
		free(map->str);
	if (map->arr)
		ft_free(map->arr);
	if (map->images)
		free_images(map);
	if (map->mlx)
		mlx_terminate(map->mlx);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

// void	texture_error(char *msg, t_map *map, t_texture *textures)
// {
// 	if (map->arr)
// 		ft_free(map->arr);
// 	if (textures->wall)
// 		mlx_delete_texture(textures->wall);
// 	if (textures->floor)
// 		mlx_delete_texture(textures->floor);
// 	free(textures);
// 	if (map->images)
// 		free_images(map);
// 	ft_putstr_fd(msg, 2);
// 	exit(EXIT_FAILURE);
// }

void	simple_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
