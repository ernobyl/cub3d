/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:10:33 by emichels          #+#    #+#             */
/*   Updated: 2024/11/27 14:59:17 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures(t_map *map, mlx_texture_t **texture, char *path)
{
	*texture = mlx_load_png(path);
	if (*texture == NULL)
		struct_error("Error\ntexture load failed\n", map);
}
