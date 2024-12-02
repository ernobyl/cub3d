/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:39:03 by emichels          #+#    #+#             */
/*   Updated: 2024/12/02 13:49:22 by emichels         ###   ########.fr       */
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

	prev_index = index - 1;
	next_index = index + 1;
	if (prev_index < 0 || next_index >= SCREEN_WIDTH)
		return ;
	check_s_and_n(prev_index, next_index, index, rays);
	check_w_and_e(prev_index, next_index, index, rays);
}

int	atoi_cub(const char *str)
{
	int		counter;
	long	result;

	counter = 0;
	result = 0;
	if (!str)
		return (-1);
	if (str[counter] == ' ')
		return (-1);
	if (str[counter] == '-')
		return (-1);
	while (str[counter] >= '0' && str[counter] <= '9')
	{	
		result = result * 10 + (str[counter++] - '0');
		if (result >= INT_MAX)
			return (INT_MAX);
	}
	if (str[counter] != ',' && str[counter] != '\n')
		return (-1);
	return (result);
}
