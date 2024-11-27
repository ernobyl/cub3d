/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:08:40 by emichels          #+#    #+#             */
/*   Updated: 2024/11/27 14:59:27 by emichels         ###   ########.fr       */
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
# include "pov_object.h"
# include <time.h>
# include "defines.h"
# include "limits.h"

typedef struct s_pov	t_pov;
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
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
	int				no;
	int				so;
	int				ea;
	int				we;
}	t_texture;

typedef struct s_image
{
	mlx_image_t	*mini_p;
	mlx_image_t	*screen;
	mlx_image_t	*minimap;
	mlx_image_t	*north;
	mlx_image_t	*south;
	mlx_image_t	*west;
	mlx_image_t	*east;
	uint32_t	color_miniwall;
	uint32_t	color_minifloor;
	uint32_t	color_player;
	uint32_t	color_wall;
	uint32_t	color_floor;
	uint32_t	color_ceiling;
	int			f_flag;
	int			c_flag;
}	t_image;

typedef struct s_ray
{
	float	angle;
	float	distance;
	float	ray_x;
	float	ray_y;
	float	ray_dir_x;
	float	ray_dir_y;
	float	prev_distance;
	float	hit_x;
	float	hit_y;
	float	perpendicular_distance;
	int		hit;
	int		hit_vertical;
	int		hit_n;
	int		hit_s;
	int		hit_w;
	int		hit_e;
	int		orientation;
	int		ray_index;
}			t_ray;

typedef struct s_tex
{
	float	texture_x;
	float	texture_y_start;
	float	texture_step;
	float	texture_y;
	int		texel_y;
	int		texel;
	int		y;
}			t_tex;

typedef struct s_gen
{
	int		player_x;
	int		player_y;
	char	player_direction;
}	t_gen;

typedef struct s_map
{
	int			fd;
	mlx_t		*mlx;
	int			y;
	int			x;
	int			max_y;
	int			max_x;
	int			duplicate;
	float		plr_y;
	float		plr_x;
	float		plr_angle;
	char		*str;
	char		**arr;
	t_image		*images;
	t_texture	*textures;
	t_pov		*sprites;
	t_ray		rays[SCREEN_WIDTH];
	int			ray_index;
	int			element_counter;
}				t_map;

// error handling
void		struct_error(char *msg, t_map *map);
void		texture_error(char *msg, t_map *map);
void		free_images(t_map *map);
void		simple_error(char *msg);
void		free_textures(t_map *map);
void		zero_map_struct(t_map *map);
void		free_sprites(t_map *map);

// player movement
void		ft_hook(void *param);
void		mousehook(double xpos, double ypos, void *param);
void		player_rotation(t_map *map, float rot_spd);
void		player_forward(t_map *map, float speed, float plr_size);
void		player_backward(t_map *map, float speed, float plr_size);
void		player_strafe_left(t_map *map, float speed, float plr_size);
void		player_strafe_right(t_map *map, float speed, float plr_size);

// display
void		load_textures(t_map *map, mlx_texture_t **texture, char *path);
void		init_minimap(t_map *map);
void		draw_arrow(t_map *map, float angle);
void		put_player(t_map *map);
void		draw_minimap(void *param);
void		safe_img_to_window(t_map *map, mlx_image_t *img, int x, int y);
void		init_3d_screen(t_map *map);
void		draw_3d_scene(t_map *map);
void		draw_floors(t_map *map, int wall_bottom);
void		draw_walls(t_map *map, int wall_top, int wall_bottom, t_ray *ray);
void		draw_ceiling(t_map *map, int ray_index, int wall_top);

void		draw_textured_wall_north(t_map *map, int wall_top,
				int wall_bottom, t_ray *ray);
void		draw_textured_wall_south(t_map *map, int wall_top,
				int wall_bottom, t_ray *ray);
void		draw_textured_wall_east(t_map *map, int wall_top,
				int wall_bottom, t_ray *ray);
void		draw_textured_wall_west(t_map *map, int wall_top,
				int wall_bottom, t_ray *ray);
void		texture_to_slice_no(t_map *map, t_tex *t,
				int wall_bottom, t_ray *ray);
void		texture_to_slice_so(t_map *map, t_tex *t,
				int wall_bottom, t_ray *ray);
void		texture_to_slice_ea(t_map *map, t_tex *t,
				int wall_bottom, t_ray *ray);
void		texture_to_slice_we(t_map *map, t_tex *t,
				int wall_bottom, t_ray *ray);
uint32_t	apply_shading(uint32_t color, float shading_factor);
void		set_default_colors(t_map *map);
void		safe_check(int index, t_ray *rays);

// Raycasting rays
void		draw_ray(t_map *map, float ray_angle, int ray_index);
void		raycasting_rays(t_map *map);
void		reset_direction(t_ray *ray);
int			check_hit(t_map *map, t_ray *ray);
int			check_diagonal(t_map *map, int x, int y, t_ray *ray);
void		check_direction(t_map *map, t_ray *ray);

// map parsing utilities
int			check_line(char *str);
void		alloc_images(t_map *map);
void		init_plr_angle(t_map *map, char direction);
int			atoi_cub(const char *str);
int			map_set_no_so(t_map *map, int i);
int			map_set_we_ea(t_map *map, int i);
int			map_set_floorcolor(t_map *map, int i);
int			map_set_ceilingcolor(t_map *map, int i);
void		map_set_color(t_map *map, char *line, int i, uint32_t *color);
int			set_texture_wall(t_map *map, mlx_texture_t **texture, int i);

// map wall checks
void		first_line(t_map *map);
void		middle_map(t_map *map, int len);
void		last_line(t_map *map);

// map handling
void		read_map(t_map *map);
void		valid_extension(char *str);
void		tabs_to_spaces(t_map *map);
void		set_map_limits(t_map *map);
void		is_rectangle(t_map *map);
void		is_valid_character(t_map *map);
void		traverse_path(char **arr, t_map *cur, int y, int x);
int			map_color_specs(t_map *map);
void		generator_map(void);
char		*run_map_gen(char *argv);

// sprites
void		create_pov_object(t_map *map);
void		animate_pov_obj(t_map *map);

#endif
