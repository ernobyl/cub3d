/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:39:03 by emichels          #+#    #+#             */
/*   Updated: 2024/11/26 11:58:27 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	safe_img_to_window(t_map *map, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(map->mlx, img, x, y) < 0)
		struct_error((char *)mlx_strerror(mlx_errno), map);
}

void	check_s_and_n(int prev_index, int next_index, int index, t_ray *rays)
{
	if (rays[prev_index].hit_n == 1 && rays[next_index].hit_n == 1
		&& rays[index].hit_n == 0)
	{
		rays[index].hit_s = 0;
		rays[index].hit_w = 0;
		rays[index].hit_e = 0;
		rays[index].hit_n = 1;
	}
	else if (rays[prev_index].hit_s == 1 && rays[next_index].hit_s == 1
		&& rays[index].hit_s == 0)
	{
		rays[index].hit_s = 1;
		rays[index].hit_w = 0;
		rays[index].hit_e = 0;
		rays[index].hit_n = 0;
	}
}

void	check_w_and_e(int prev_index, int next_index, int index, t_ray *rays)
{
	if (rays[prev_index].hit_w == 1 && rays[next_index].hit_w == 1
		&& rays[index].hit_w == 0)
	{
		rays[index].hit_s = 0;
		rays[index].hit_w = 1;
		rays[index].hit_e = 0;
		rays[index].hit_n = 0;
	}
	else if (rays[prev_index].hit_e == 1 && rays[next_index].hit_e == 1
		&& rays[index].hit_e == 0)
	{
		rays[index].hit_s = 0;
		rays[index].hit_w = 0;
		rays[index].hit_e = 1;
		rays[index].hit_n = 0;
	}
}

void	safe_check(int index, t_ray *rays)
{
	int	prev_index;
	int	next_index;

	prev_index = index - 2;
	next_index = index + 2;
	if (prev_index < 0 || next_index >= SCREEN_WIDTH)
		return ;
	check_s_and_n(prev_index, next_index, index, rays);
	check_w_and_e(prev_index, next_index, index, rays);
}
