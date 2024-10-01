/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:26:02 by msilfver          #+#    #+#             */
/*   Updated: 2024/10/01 15:09:45 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    ft_hook(void *param)
{
    t_map   *map;
    mlx_t   *mlx;
    double  factor;

    map = (void *)param;
    mlx = map->mlx;
    factor = 0.2;
    if (mlx_is_key_down(mlx, MLX_KEY_W))
       map->images->mini_p->instances->y -= 1;
    else if (mlx_is_key_down(mlx, MLX_KEY_S))
       map->images->mini_p->instances->y += 1;
    else if (mlx_is_key_down(mlx, MLX_KEY_D))
       map->images->mini_p->instances->x += 1;
    else if (mlx_is_key_down(mlx, MLX_KEY_A))
       map->images->mini_p->instances->x -= 1;
    else if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}