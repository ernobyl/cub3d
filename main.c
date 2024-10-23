/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:40:26 by emichels          #+#    #+#             */
/*   Updated: 2024/10/23 13:05:42 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	zero_map_struct(t_map *map)
{
	map->fd = 0;
	map->mlx = NULL;
	map->y = 0;
	map->x = 0;
	map->max_y = 0;
	map->max_x = 0;
	map->plr_y = 0.0f;
	map->plr_x = 0.0f;
	map->plr_angle = 0.0f;
	map->str = NULL;
	map->arr = NULL;
	map->images = NULL;
	map->rays->angle = 0;
	map->rays->distance = 0;
	map->rays->hit_x = 0;
	map->rays->hit_y = 0;
}

static void	inspect_map(t_map *map)
{
	set_map_limits(map);
	is_valid_character(map);
	is_rectangle(map);
}

static void	assign_map(t_map *map)
{
	read_map(map);
	tabs_to_spaces(map);
	inspect_map(map);
	map->arr = ft_split(map->str, '\n');
	if (!map->arr)
		struct_error("Error\nstring split failed\n", map);
}

static void	free_map_struct(t_map map)
{
	if (map.str)
		free(map.str);
	if (map.arr)
		ft_free(map.arr);
	//free_images(&map);
}
/* void	set_background(t_map *map, mlx_image_t *bg_image)
{
	mlx_texture_t *background;
	

	background = mlx_load_png("./textures/test.png");
	bg_image = mlx_texture_to_image(map->mlx, background);
	mlx_delete_texture(background);
	mlx_resize_image(bg_image, WINDOW_HEIGHT, WINDOW_HEIGHT);
	mlx_image_to_window(map->mlx, bg_image, 0, 0);
} */

int32_t	main(int argc, char **argv)
{
	t_map	map;
	//mlx_image_t		bg_image;

	if (argc != 2)
		simple_error("Error\ninvalid argument count\n");
	zero_map_struct(&map);
	valid_extension(argv[1]);
	map.fd = open(argv[1], O_RDONLY);
	if (map.fd == -1)
		struct_error("Error\nfile open error\n", &map);
	assign_map(&map);
	printf("ceiling color after assign_map: 0x%08X\n", map.images->color_ceiling);
	printf("floor color after assign_map: 0x%08X\n", map.images->color_floor);
	for (int i = 0; map.arr[i]; i++)
		printf("%s\n", map.arr[i]);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	map.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
	if (!map.mlx)
		struct_error((char *)mlx_strerror(mlx_errno), &map);
	//set_background(&map, &bg_image);
	//display_map(&map);
	mlx_set_cursor_mode(map.mlx, MLX_MOUSE_HIDDEN);
	//printf("ceiling color before init_minimap: 0x%08X\n", map.images->color_ceiling);
	//printf("floor color before init_minimap: 0x%08X\n", map.images->color_floor);
	init_minimap(&map);
	printf("ceiling color after init_minimap: 0x%08X\n", map.images->color_ceiling);
	printf("floor color after init_minimap: 0x%08X\n", map.images->color_floor);
	init_3d_screen(&map);
	//init_miniplayer(&map);
	printf("plr x: %f\n", map.plr_x);
	printf("plr y: %f\n", map.plr_y);
	mlx_loop_hook(map.mlx, ft_hook, &map);
	draw_minimap(&map);
	put_player(&map);
	//mlx_loop_hook(map.mlx, put_player, &map);
	mlx_cursor_hook(map.mlx, &mousehook, &map);
	mlx_loop(map.mlx);
	free_map_struct(map);
	mlx_terminate(map.mlx);
	//zero_map_struct(&map);
	return (0);
}
