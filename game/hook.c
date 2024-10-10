/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:26:02 by msilfver          #+#    #+#             */
/*   Updated: 2024/10/10 12:46:08 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    ft_hook(void *param)
{
	t_map   *map;
	mlx_t   *mlx;
	float	speed;
	float	rot_spd;

	map = (void *)param;
	mlx = map->mlx;
	speed = 1.0f;
	rot_spd = 0.05f;
	// if (mlx_is_key_down(mlx, MLX_KEY_W))
	// {
	// 	map->plr_y -= (speed / (float)MINIHEIGHT);
	// 	if (map->arr[(int)map->plr_y][(int)map->plr_x] == '1')
	// 		map->plr_y += (speed / (float)MINIHEIGHT);
	// 	else
	// 		map->images->mini_p->instances->y -= speed;
	// 	printf("plr x: %f\n", map->plr_x);
	// 	printf("plr y: %f\n", map->plr_y);
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_S))
	// {
	// 	map->plr_y += (speed / (float)MINIHEIGHT);
	// 	if (map->arr[(int)map->plr_y][(int)map->plr_x] == '1')
	// 		map->plr_y -= (speed / (float)MINIHEIGHT);
	// 	else
	// 		map->images->mini_p->instances->y += speed;
	// 	printf("plr x: %f\n", map->plr_x);
	// 	printf("plr y: %f\n", map->plr_y);
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_D))
	// {
	// 	map->plr_x += (speed / (float)MINIWIDTH);
	// 	if (map->arr[(int)map->plr_y][(int)map->plr_x] == '1')
	// 		map->plr_x -= (speed / (float)MINIWIDTH);
	// 	else
	// 		map->images->mini_p->instances->x += speed;
	// 	printf("plr x: %f\n", map->plr_x);
	// 	printf("plr y: %f\n", map->plr_y);
	// }
	// if (mlx_is_key_down(mlx, MLX_KEY_A))
	// {
	// 	map->plr_x -= (speed / (float)MINIWIDTH);
	// 	if (map->arr[(int)map->plr_y][(int)map->plr_x] == '1')
	// 		map->plr_x += (speed / (float)MINIWIDTH);
	// 	else
	// 		map->images->mini_p->instances->x -= speed;
	// 	printf("plr x: %f\n", map->plr_x);
	// 	printf("plr y: %f\n", map->plr_y);
	// }
	// yritys saada liikkumiseen kaantyminen yms.
	if (mlx_is_key_down(mlx, MLX_KEY_A))
    {
        map->plr_angle -= rot_spd;
        if (map->plr_angle < 0.0f)
            map->plr_angle += 2 * PI;
        printf("Player angle: %f\n", map->plr_angle);
    }

    if (mlx_is_key_down(mlx, MLX_KEY_D))
    {
        map->plr_angle += rot_spd;
        if (map->plr_angle >= 2 * PI)
            map->plr_angle -= 2 * PI;
        printf("Player angle: %f\n", map->plr_angle);
    }

    if (mlx_is_key_down(mlx, MLX_KEY_W))
    {
        map->plr_x += (cos(map->plr_angle) * speed / MINIWIDTH);
        map->plr_y += (sin(map->plr_angle) * speed / MINIHEIGHT);

        // tassa instancen siirtamisessa on jotain vikaa,
		//	koordinaatit nayttais paivittyvan melko jarkevasti
        if (map->arr[(int)map->plr_y][(int)map->plr_x] != '1')
        {
            map->images->mini_p->instances->x += (map->plr_x / MINIWIDTH);
            map->images->mini_p->instances->y += (map->plr_y / MINIHEIGHT);
        }

        printf("Player position - x: %f, y: %f\n", map->plr_x, map->plr_y);
    }

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}