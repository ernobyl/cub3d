/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:39:03 by emichels          #+#    #+#             */
/*   Updated: 2024/11/04 12:06:10 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	safe_img_to_window(t_map *map, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(map->mlx, img, x, y) < 0)
		struct_error((char *)mlx_strerror(mlx_errno), map);
}
