/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:28:42 by emichels          #+#    #+#             */
/*   Updated: 2024/11/20 22:37:21 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_rotation(t_map *map, float rot_spd)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->plr_angle -= rot_spd;
		if (map->plr_angle < 0.0f)
			map->plr_angle += 2 * PI;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->plr_angle += rot_spd;
		if (map->plr_angle >= 2 * PI)
			map->plr_angle -= 2 * PI;
	}
}

void	player_forward(t_map *map, float speed, float plr_size)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		map->plr_x += (cos(map->plr_angle) * speed / MINIWIDTH);
		map->plr_y += (sin(map->plr_angle) * speed / MINIHEIGHT);
		if ((map->arr[(int)(map->plr_y + plr_size)]
			[(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)]
			[(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y + plr_size)]
			[(int)(map->plr_x - plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)]
			[(int)(map->plr_x - plr_size)] == '1'))
		{
			map->plr_x -= (cos(map->plr_angle) * speed / MINIWIDTH);
			map->plr_y -= (sin(map->plr_angle) * speed / MINIHEIGHT);
		}
		else
		{
			map->images->mini_p->instances->x = (map->plr_x - 0.5f) * MINIWIDTH;
			map->images->mini_p->instances->y
				= (map->plr_y - 0.5f) * MINIHEIGHT;
		}
	}
}

void	player_backward(t_map *map, float speed, float plr_size)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	{
		map->plr_x -= (cos(map->plr_angle) * speed / MINIWIDTH);
		map->plr_y -= (sin(map->plr_angle) * speed / MINIHEIGHT);
		if ((map->arr[(int)(map->plr_y + plr_size)]
			[(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)]
			[(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y + plr_size)]
			[(int)(map->plr_x - plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)]
			[(int)(map->plr_x - plr_size)] == '1'))
		{
			map->plr_x += (cos(map->plr_angle) * speed / MINIWIDTH);
			map->plr_y += (sin(map->plr_angle) * speed / MINIHEIGHT);
		}
		else
		{
			map->images->mini_p->instances->x = (map->plr_x - 0.5f) * MINIWIDTH;
			map->images->mini_p->instances->y
				= (map->plr_y - 0.5f) * MINIHEIGHT;
		}
	}
}

void	player_strafe_left(t_map *map, float speed, float plr_size)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		map->plr_x -= (cos(map->plr_angle + PI / 2) * speed / MINIWIDTH);
		map->plr_y -= (sin(map->plr_angle + PI / 2) * speed / MINIHEIGHT);
		if ((map->arr[(int)(map->plr_y + plr_size)]
			[(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)]
			[(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y + plr_size)]
			[(int)(map->plr_x - plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)]
			[(int)(map->plr_x - plr_size)] == '1'))
		{
			map->plr_x += (cos(map->plr_angle + PI / 2) * speed / MINIWIDTH);
			map->plr_y += (sin(map->plr_angle + PI / 2) * speed / MINIHEIGHT);
		}
		else
		{
			map->images->mini_p->instances->x = (map->plr_x - 0.5f) * MINIWIDTH;
			map->images->mini_p->instances->y
				= (map->plr_y - 0.5f) * MINIHEIGHT;
		}
	}
}

void	player_strafe_right(t_map *map, float speed, float plr_size)
{
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		map->plr_x += (cos(map->plr_angle + PI / 2) * speed / MINIWIDTH);
		map->plr_y += (sin(map->plr_angle + PI / 2) * speed / MINIHEIGHT);
		if ((map->arr[(int)(map->plr_y + plr_size)]
			[(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)]
			[(int)(map->plr_x + plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y + plr_size)]
			[(int)(map->plr_x - plr_size)] == '1')
			|| (map->arr[(int)(map->plr_y - plr_size)]
			[(int)(map->plr_x - plr_size)] == '1'))
		{
			map->plr_x -= (cos(map->plr_angle + PI / 2) * speed / MINIWIDTH);
			map->plr_y -= (sin(map->plr_angle + PI / 2) * speed / MINIHEIGHT);
		}
		else
		{
			map->images->mini_p->instances->x = (map->plr_x - 0.5f) * MINIWIDTH;
			map->images->mini_p->instances->y
				= (map->plr_y - 0.5f) * MINIHEIGHT;
		}
	}
}
