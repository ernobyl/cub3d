/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:26:02 by msilfver          #+#    #+#             */
/*   Updated: 2024/10/01 17:17:32 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    ft_hook(void *param)
{
	t_map   *map;
	mlx_t   *mlx;
	float	speed;
	//double  factor;

	map = (void *)param;
	mlx = map->mlx;
	speed = 1.0f;
	//factor = 0.2;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		map->plr_y -= (speed / (float)MINIHEIGHT);
		if (map->arr[(int)map->plr_y][(int)map->plr_x] == '1')
			map->plr_y += (speed / (float)MINIHEIGHT);
		else
			map->images->mini_p->instances->y -= speed;
		printf("plr x: %f\n", map->plr_x);
		printf("plr y: %f\n", map->plr_y);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		map->plr_y += (speed / (float)MINIHEIGHT);
		if (map->arr[(int)map->plr_y][(int)map->plr_x] == '1')
			map->plr_y -= (speed / (float)MINIHEIGHT);
		else
			map->images->mini_p->instances->y += speed;
		printf("plr x: %f\n", map->plr_x);
		printf("plr y: %f\n", map->plr_y);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		map->plr_x += (speed / (float)MINIWIDTH);
		if (map->arr[(int)map->plr_y][(int)map->plr_x] == '1')
			map->plr_x -= (speed / (float)MINIWIDTH);
		else
			map->images->mini_p->instances->x += speed;
		printf("plr x: %f\n", map->plr_x);
		printf("plr y: %f\n", map->plr_y);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		map->plr_x -= (speed / (float)MINIWIDTH);
		if (map->arr[(int)map->plr_y][(int)map->plr_x] == '1')
			map->plr_x += (speed / (float)MINIWIDTH);
		else
			map->images->mini_p->instances->x -= speed;
		printf("plr x: %f\n", map->plr_x);
		printf("plr y: %f\n", map->plr_y);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}