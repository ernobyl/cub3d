/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:41:07 by emichels          #+#    #+#             */
/*   Updated: 2024/04/16 13:28:07 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	move_right(t_map *map)
{
	if (map->arr[map->plr_y][map->plr_x + 1] == '1')
		return ;
	map->plr_x++;
	map->images->p_img->instances->x += WIDTH;
	count_steps(map);
	count_collectibles(map);
	exit_open(map);
}

static void	move_left(t_map *map)
{
	if (map->arr[map->plr_y][map->plr_x - 1] == '1')
		return ;
	map->plr_x--;
	map->images->p_img->instances->x -= WIDTH;
	count_steps(map);
	count_collectibles(map);
	exit_open(map);
}

static void	move_down(t_map *map)
{
	if (map->arr[map->plr_y + 1][map->plr_x] == '1')
		return ;
	map->plr_y++;
	map->images->p_img->instances->y += HEIGHT;
	count_steps(map);
	count_collectibles(map);
	exit_open(map);
}

static void	move_up(t_map *map)
{
	if (map->arr[map->plr_y - 1][map->plr_x] == '1')
		return ;
	map->plr_y--;
	map->images->p_img->instances->y -= HEIGHT;
	count_steps(map);
	count_collectibles(map);
	exit_open(map);
}

void	wasd_keyhook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_right(map);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_left(map);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_down(map);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_up(map);
}
