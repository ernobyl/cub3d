/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:26:02 by msilfver          #+#    #+#             */
/*   Updated: 2024/10/30 09:57:08 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    ft_hook(void *param)
{
	t_map   *map;
	mlx_t   *mlx;
	float   speed;
	float   rot_spd;
	float	plr_size;

	map = (t_map *)param;
	mlx = map->mlx;
	speed = 1.0f;
	rot_spd = 0.08f;
	plr_size = 0.1f;
	// rotation
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		map->plr_angle -= rot_spd;
		if (map->plr_angle < 0.0f)
			map->plr_angle += 2 * PI;	
		//printf("Player angle: %f\n", map->plr_angle);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
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
		if ((map->arr[(int)(map->plr_y + plr_size)][(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)][(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y + plr_size)][(int)(map->plr_x - plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)][(int)(map->plr_x - plr_size)] == '1'))
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
		if ((map->arr[(int)(map->plr_y + plr_size)][(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)][(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y + plr_size)][(int)(map->plr_x - plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)][(int)(map->plr_x - plr_size)] == '1'))
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
	// strafe left
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
			map->plr_x -= (cos(map->plr_angle + PI / 2) * speed / MINIWIDTH);
			map->plr_y -= (sin(map->plr_angle + PI / 2) * speed / MINIHEIGHT);
			// wall collision
			if ((map->arr[(int)(map->plr_y + plr_size)][(int)(map->plr_x + plr_size)] == '1')
				|| (map->arr[(int)(map->plr_y - plr_size)][(int)(map->plr_x + plr_size)] == '1')
				|| (map->arr[(int)(map->plr_y + plr_size)][(int)(map->plr_x - plr_size)] == '1')
				|| (map->arr[(int)(map->plr_y - plr_size)][(int)(map->plr_x - plr_size)] == '1'))
			{
				map->plr_x += (cos(map->plr_angle + PI / 2) * speed / MINIWIDTH);
				map->plr_y += (sin(map->plr_angle + PI / 2) * speed / MINIHEIGHT);
			}
			else
			{
				map->images->mini_p->instances->x = (map->plr_x - 0.5f) * MINIWIDTH;
				map->images->mini_p->instances->y = (map->plr_y - 0.5f) * MINIHEIGHT;
			}
	}
	// strafe right
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		map->plr_x += (cos(map->plr_angle + PI / 2) * speed / MINIWIDTH);
		map->plr_y += (sin(map->plr_angle + PI / 2) * speed / MINIHEIGHT);
		// wall collision
		if ((map->arr[(int)(map->plr_y + plr_size)][(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)][(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y + plr_size)][(int)(map->plr_x - plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)][(int)(map->plr_x - plr_size)] == '1'))
		{
			map->plr_x -= (cos(map->plr_angle + PI / 2) * speed / MINIWIDTH);
			map->plr_y -= (sin(map->plr_angle + PI / 2) * speed / MINIHEIGHT);
		}
		else
		{
			map->images->mini_p->instances->x = (map->plr_x - 0.5f) * MINIWIDTH;
			map->images->mini_p->instances->y = (map->plr_y - 0.5f) * MINIHEIGHT;
		}
	}
	// redraw rotated arrow
	mlx_delete_image(mlx, map->images->mini_p);
	map->images->mini_p = mlx_new_image(map->mlx, 256, 256);
	draw_arrow(map, map->plr_angle);
	// update arrow at current location
	safe_img_to_window(map, map->images->mini_p, 
		(map->plr_x * MINIWIDTH) - 256 / 2, 
		(map->plr_y * MINIHEIGHT) - 256 / 2);
	draw_3d_scene(map);

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void mousehook(double xpos, double ypos, void *param)
{
	t_map *map;
	static double last_x = 0.0;
	double sensitivity;
	double delta_x;
	
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


