/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:26:02 by msilfver          #+#    #+#             */
/*   Updated: 2024/10/22 10:33:16 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    ft_hook(void *param)
{
	t_map   *map;
	mlx_t   *mlx;
	float   speed;
	float   rot_spd;

	map = (t_map *)param;
	mlx = map->mlx;
	speed = 1.0f;
	rot_spd = 0.08f;
	// rotation
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		map->plr_angle -= rot_spd;
		if (map->plr_angle < 0.0f)
			map->plr_angle += 2 * PI;	
		//printf("Player angle: %f\n", map->plr_angle);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		map->plr_angle += rot_spd;
		if (map->plr_angle >= 2 * PI)
			map->plr_angle -= 2 * PI;
		//printf("Player angle: %f\n", map->plr_angle);
	}
	// forward
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		map->plr_x += (cos(map->plr_angle) * speed / MINIWIDTH);
		map->plr_y += (sin(map->plr_angle) * speed / MINIHEIGHT);
		// wall collision
		if (map->arr[(int)map->plr_y][(int)map->plr_x] == '1')
		{
			map->plr_x -= (cos(map->plr_angle) * speed / MINIWIDTH);
			map->plr_y -= (sin(map->plr_angle) * speed / MINIHEIGHT);
		}
		else
		{
			map->images->mini_p->instances->x = (map->plr_x - 0.5f) * MINIWIDTH;
			map->images->mini_p->instances->y = (map->plr_y - 0.5f) * MINIHEIGHT;
		}
		//printf("Player position - x: %f, y: %f\n", map->plr_x, map->plr_y);
	}
	// backward
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		map->plr_x -= (cos(map->plr_angle) * speed / MINIWIDTH);
		map->plr_y -= (sin(map->plr_angle) * speed / MINIHEIGHT);
		// wall collision
		if (map->arr[(int)map->plr_y][(int)map->plr_x] == '1')
		{
			map->plr_x += (cos(map->plr_angle) * speed / MINIWIDTH);
			map->plr_y += (sin(map->plr_angle) * speed / MINIHEIGHT);
		}
		else
		{
			map->images->mini_p->instances->x = (map->plr_x - 0.5f) * MINIWIDTH;
			map->images->mini_p->instances->y = (map->plr_y - 0.5f) * MINIHEIGHT;
		}
		//printf("Player position - x: %f, y: %f\n", map->plr_x, map->plr_y);

	}
	// redraw rotated arrow
	mlx_delete_image(mlx, map->images->mini_p);
	map->images->mini_p = mlx_new_image(map->mlx, 256, 256);
	draw_arrow(map, map->plr_angle);
	// update arrow at current location
	mlx_image_to_window(map->mlx, map->images->mini_p, 
		(map->plr_x * MINIWIDTH) - 256 / 2, 
		(map->plr_y * MINIHEIGHT) - 256 / 2);

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}
