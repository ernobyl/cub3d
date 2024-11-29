/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:40:26 by emichels          #+#    #+#             */
/*   Updated: 2024/11/29 12:11:30 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	inspect_map(t_map *map)
{
	set_map_limits(map);
	is_valid_character(map);
	is_valid(map);
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
	free_textures(&map);
	free_images(&map);
}

int32_t	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		simple_error("Error\ninvalid argument count\n");
	zero_map_struct(&map);
	valid_extension(argv[1]);
	map.fd = open(argv[1], O_RDONLY);
	if (map.fd == -1)
		struct_error("Error\nfile open error\n", &map);
	assign_map(&map);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	map.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
	if (!map.mlx)
		struct_error((char *)mlx_strerror(mlx_errno), &map);
	init_3d_screen(&map);
	mlx_set_cursor_mode(map.mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(map.mlx, ft_hook, &map);
	put_player(&map);
	mlx_loop(map.mlx);
	free_map_struct(map);
	mlx_terminate(map.mlx);
	return (0);
}
