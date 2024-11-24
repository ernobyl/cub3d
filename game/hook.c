/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:26:02 by msilfver          #+#    #+#             */
/*   Updated: 2024/11/24 16:47:03 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	refresh_mini_p(t_map *map)
{
	mlx_delete_image(map->mlx, map->images->mini_p);
	map->images->mini_p = mlx_new_image(map->mlx, 256, 256);
	draw_arrow(map, map->plr_angle);
	safe_img_to_window(map, map->images->mini_p,
		(map->plr_x * MINIWIDTH) - 256 / 2,
		(map->plr_y * MINIHEIGHT) - 256 / 2);
}

void	ft_hook(void *param)
{
	t_map	*map;
	float	speed;
	float	rot_spd;
	float	plr_size;

	map = (t_map *)param;
	speed = 1.5f;
	rot_spd = 0.1f;
	plr_size = 0.1f;
	player_rotation(map, rot_spd);
	player_forward(map, speed, plr_size);
	player_backward(map, speed, plr_size);
	player_strafe_left(map, speed, plr_size);
	player_strafe_right(map, speed, plr_size);
	refresh_mini_p(map);
	raycasting_rays(map);
	draw_3d_scene(map);
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
}

void	mousehook(double xpos, double ypos, void *param)
{
	t_map			*map;
	static double	last_x = 0.0;
	double			sensitivity;
	double			delta_x;

	(void)ypos;
	map = (t_map *)param;
	sensitivity = 0.005;
	if (last_x == 0.0)
		last_x = xpos;
	delta_x = xpos - last_x;
	last_x = xpos;
	map->plr_angle += delta_x * sensitivity;
	if (map->plr_angle < 0)
		map->plr_angle += 2 * PI;
	if (map->plr_angle >= 2 * PI)
		map->plr_angle -= 2 * PI;
}
