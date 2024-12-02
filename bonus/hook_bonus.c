/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:26:02 by msilfver          #+#    #+#             */
/*   Updated: 2024/12/02 17:26:22 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static uint32_t	convert_colors(uint32_t color)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = color & 0xFF;
	g = (color >> 8) & 0xFF;
	b = (color >> 16) & 0xFF;
	a = (color >> 24) & 0xFF;
	color = (b << 24) | (g << 16) | (r << 8) | a;
	return (color);
}

void	set_background(t_map *map)
{
	mlx_texture_t	*bg_texture;
	uint32_t		color;
	int				texture_x;
	int				texture_y;

	bg_texture = mlx_load_png("./textures/night.png");
	if (!bg_texture)
		return ;
	map->y = 0;
	while (map->y < SCREEN_HEIGHT)
	{
		map->x = 0;
		while (map->x < SCREEN_WIDTH)
		{
			texture_x = map->x % bg_texture->width;
			texture_y = map->y % bg_texture->height;
			color = ((uint32_t *)bg_texture->pixels)[texture_y
				* bg_texture->width + texture_x];
			color = convert_colors(color);
			mlx_put_pixel(map->images->screen, map->x, map->y, color);
			map->x++;
		}
		map->y++;
	}
	mlx_delete_texture(bg_texture);
}

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
	set_background(map);
	draw_3d_scene(map);
	animate_pov_obj(map);
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
