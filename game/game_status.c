/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:49:24 by emichels          #+#    #+#             */
/*   Updated: 2024/04/16 13:17:00 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	count_steps(t_map *map)
{
	map->steps++;
	ft_putstr_fd("step count: ", 1);
	ft_putnbr_fd(map->steps, 1);
	ft_putchar_fd('\n', 1);
}

void	count_collectibles(t_map *map)
{
	int	i;

	if (map->arr[map->plr_y][map->plr_x] == 'C')
	{
		map->arr[map->plr_y][map->plr_x] = '0';
		i = 0;
		while (map->collect_n)
		{
			if (map->images->c_img->instances[i].x
				== map->images->p_img->instances->x
				&& map->images->c_img->instances[i].y
				== map->images->p_img->instances->y)
				break ;
			i++;
		}
		map->images->c_img->instances[i].enabled = false;
		map->collect_n--;
	}
}

void	exit_open(t_map *map)
{
	if (map->collect_n == 0)
	{
		map->images->dc_img->enabled = false;
		map->images->do_img->enabled = true;
		if (map->arr[map->plr_y][map->plr_x] == 'E')
			mlx_close_window(map->mlx);
	}
}
