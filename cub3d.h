/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:08:40 by emichels          #+#    #+#             */
/*   Updated: 2024/11/01 19:44:54 by msilfver         ###   ########.fr       */
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
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define MINIWIDTH 4
# define MINIHEIGHT 4
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define FOV 90
# define MAX_RENDER_DISTANCE 320
# define PI 3.141592f
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define RED 0xFF0000FF
# define YELLOW 0xFFFF00FF
# define BLUE 0x0000FFFF
# define GREEN 0x00FF00FF
# define WHITE_TP 0xFFFFFF80
# define BLACK_TP 0x00000080
# define RED_TP 0xFF000080
# define YELLOW_TP 0xFFFF0080

typedef struct s_point
{
	int x;
	int y;
}	t_point;

typedef struct s_line
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
}	t_line;

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
	int	delta_x;
	int	delta_y;
	int	step_x;
	int	step_y;
}	t_tri;

typedef struct s_texture
{
	mlx_texture_t	*wall_no;
	mlx_texture_t	*wall_so;
	mlx_texture_t	*wall_we;
	mlx_texture_t	*wall_ea;
}	t_texture;

typedef struct s_image
{
	mlx_image_t	*mini_p;
	mlx_image_t	*mini_w;
	mlx_image_t	*mini_f;
	mlx_image_t	*w_img;
	mlx_image_t	*f_img;
	mlx_image_t *screen;
	mlx_image_t	*minimap;
	uint32_t	color_miniwall;
	uint32_t	color_minifloor;
	uint32_t	color_player;
	uint32_t	color_wall;
	uint32_t	color_floor;
	uint32_t	color_ceiling;
}	t_image;

typedef struct s_ray
{
    float 	angle;
    float 	distance;
    float 	ray_x;
    float 	ray_y;
	float 	ray_dir_x;
	float	ray_dir_y;
    int 	hit_x;
    int 	hit_y;
    int 	hit;
	int		hit_vertical;
	int		orientation;
} t_ray;

typedef struct s_map
{
	int			fd;
	mlx_t		*mlx;
	int			y;
	int			x;
	int			max_y;
	int			max_x;
	float		plr_y;
	float		plr_x;
	float		plr_angle;
	char		*str;
	char		**arr;
	t_image		*images;
	t_texture	*textures;
	t_ray 		rays[640];
}	t_map;

// error handling
void	struct_error(char *msg, t_map *map);
void	texture_error(char *msg, t_map *map);
//void	free_textures(t_texture *textures);
void	free_images(t_map *map);
void	simple_error(char *msg);

// player movement
void    ft_hook(void *param);
void	mousehook(double xpos, double ypos, void *param);

// display
void		resize_images(t_map *map);
void		load_textures(t_map *map, mlx_texture_t **texture, char *path);
void		load_images(t_map *map, t_texture *textures);
void		init_minimap(t_map *map);
void		init_miniplayer(t_map *map);
void		draw_arrow(t_map *map, float angle);
void		put_player(t_map *map);
void		draw_minimap(void* param);
void		draw_floor(void* param);
void		display_map(t_map *map);
void		safe_img_to_window(t_map *map, mlx_image_t *img, int x, int y);
void		init_3d_screen(t_map *map);
void		draw_3d_scene(t_map *map);
void 		draw_textured_wall_north(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray);
void 		draw_textured_wall_south(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray);
void		draw_textured_wall_east(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray);
void		draw_textured_wall_west(t_map *map, int ray_index, int wall_top, int wall_bottom, t_ray *ray);
uint32_t	apply_shading(uint32_t color, float shading_factor);

// Raycasting rays
void draw_ray(t_map *map, float ray_angle, int ray_index);
void raycasting_rays(t_map *map);

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
