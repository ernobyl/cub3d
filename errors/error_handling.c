/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:23:58 by emichels          #+#    #+#             */
/*   Updated: 2024/11/22 20:18:38 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	debug_map(t_map *map)
{
	printf("Invalid map element at x: %i y: %i\n", map->x + 1, map->y + 1);
}

void	texture_error(char *msg, t_map *map)
{
	free_textures(map);
	if (map->arr)
		ft_free(map->arr);
	if (map->images)
		free_images(map);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	struct_error(char *msg, t_map *map)
{
	if (ft_strcmp(msg, "Error\nmap not walled\n") == 0)
		debug_map(map);
	if (map->str)
		free(map->str);
	if (map->arr)
		ft_free(map->arr);
	if (map->textures)
		free_textures(map);
	if (map->sprites)
		free_sprites(map);
	if (map->images)
		free_images(map);
	if (map->mlx)
		mlx_terminate(map->mlx);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	simple_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
