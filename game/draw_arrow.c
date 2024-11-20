/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:17:06 by emichels          #+#    #+#             */
/*   Updated: 2024/11/20 23:15:25 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_line(t_line *line, t_point *start, t_point *end)
{
	line->dx = ft_abs(end->x - start->x);
	line->dy = ft_abs(end->y - start->y);
	if (start->x < end->x)
		line->sx = 1;
	else
		line->sx = -1;
	if (start->y < end->y)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
}

void	draw_line(t_map *map, t_point start, t_point end)
{
	t_line	line;
	int		err2;

	init_line(&line, &start, &end);
	while (1)
	{
		mlx_put_pixel(map->images->mini_p, start.x, start.y, YELLOW);
		if (start.x == end.x && start.y == end.y)
			break ;
		err2 = 2 * line.err;
		if (err2 > -line.dy)
		{
			line.err -= line.dy;
			start.x += line.sx;
		}
		if (err2 < line.dx)
		{
			line.err += line.dx;
			start.y += line.sy;
		}
	}
}

void	set_triangle_points(t_tri *tri, float angle, int length, int width)
{
	tri->tip_x = tri->center_x + (int)(cos(angle) * length);
	tri->tip_y = tri->center_y + (int)(sin(angle) * length);
	tri->base_left_x
		= tri->center_x + (int)(cos(angle + (PI / 2)) * (width / 2));
	tri->base_left_y
		= tri->center_y + (int)(sin(angle + (PI / 2)) * (width / 2));
	tri->base_right_x
		= tri->center_x + (int)(cos(angle - (PI / 2)) * (width / 2));
	tri->base_right_y
		= tri->center_y + (int)(sin(angle - (PI / 2)) * (width / 2));
}

void	init_triangle(t_tri *tri)
{
	tri->tip_x = 0;
	tri->tip_y = 0;
	tri->base_left_x = 0;
	tri->base_left_y = 0;
	tri->base_right_x = 0;
	tri->base_right_y = 0;
	tri->center_x = 256 / 2;
	tri->center_y = 256 / 2;
}

void	draw_arrow(t_map *map, float angle)
{
	t_tri	tri;
	t_point	start;
	t_point	end;
	int		length;
	int		width;

	init_triangle(&tri);
	length = 12;
	width = 8;
	set_triangle_points(&tri, angle, length, width);
	start.x = tri.base_left_x;
	start.y = tri.base_left_y;
	end.x = tri.tip_x;
	end.y = tri.tip_y;
	draw_line(map, start, end);
	start.x = tri.base_right_x;
	start.y = tri.base_right_y;
	draw_line(map, start, end);
	start.x = tri.base_left_x;
	start.y = tri.base_left_y;
	end.x = tri.base_right_x;
	end.y = tri.base_right_y;
	draw_line(map, start, end);
	raycasting_rays(map);
}
