/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:08:40 by emichels          #+#    #+#             */
/*   Updated: 2024/10/17 09:37:14 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"
# include "MLX42/MLX42.h"

# define BUFFERSIZE 25
# define WIDTH 32
# define HEIGHT 32
# define MINIWIDTH 16
# define MINIHEIGHT 16
# define PI 3.141592f
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define RED 0xFF0000FF
# define YELLOW 0xFFFF00FF

typedef struct s_tri
{
	int	tip_x;
	int	tip_y;
	int	base_left_x;
	int	base_left_y;
	int	base_right_x;
	int	base_right_y;
	int	center_x;
	int	center_y;
}	t_tri;

typedef struct s_texture
{
	mlx_texture_t	*wall;
	mlx_texture_t	*floor;
}	t_texture;

typedef struct s_image
{
	mlx_image_t	*mini_p;
	mlx_image_t	*mini_w;
	mlx_image_t	*mini_f;
	mlx_image_t	*w_img;
	mlx_image_t	*f_img;
	mlx_image_t	*minimap;
	uint32_t	color_miniwall;
	uint32_t	color_minifloor;
	uint32_t	color_player;
	uint32_t	color_wall;
	uint32_t	color_floor;
	uint32_t	color_ceiling;
}	t_image;

typedef	struct s_ray
{
	float	angle;
	float	distance;
	int		hit_x;
	int		hit_y;
} t_ray;

typedef struct s_map
{
	int		fd;
	mlx_t	*mlx;
	int		y;
	int		x;
	int		max_y;
	int		max_x;
	float	plr_y;
	float	plr_x;
	float	plr_angle;
	char	*str;
	char	**arr;
	t_image	*images;
	t_ray 	rays[3];
}	t_map;

	// indented prototypes are unmodified from so_long
// error handling
void	struct_error(char *msg, t_map *map);
//void	texture_error(char *msg, t_map *map, t_texture *textures);
//void	free_textures(t_texture *textures);
void	free_images(t_map *map);
void	simple_error(char *msg);

// player movement & status
	void	wasd_keyhook(mlx_key_data_t keydata, void *param);
	void	count_steps(t_map *map);
	void	count_collectibles(t_map *map);
	void	exit_open(t_map *map);
	void    ft_hook(void *param);

// display
	void	resize_images(t_map *map);
	void	load_textures(t_map *map);
	void	load_images(t_map *map, t_texture *textures);
void	init_minimap(t_map *map);
void	init_miniplayer(t_map *map);
void	draw_arrow(t_map *map, float angle);
void	put_player(t_map *map);
void	draw_minimap(void* param);
void	draw_floor(void* param);
void	display_map(t_map *map);
void	safe_img_to_window(t_map *map, mlx_image_t *img);
void	draw_ray(t_map *map, float ray_angle, int ray_index);

// map handling
void	read_map(t_map *map);
void	valid_extension(char *str);
void	tabs_to_spaces(t_map *map);
void	set_map_limits(t_map *map);
void	is_rectangle(t_map *map);
void	is_valid_character(t_map *map);
void	traverse_path(char **arr, t_map *cur, int y, int x);
int		map_color_specs(t_map *map);

#endif
