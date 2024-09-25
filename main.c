/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:40:26 by emichels          #+#    #+#             */
/*   Updated: 2024/09/25 13:48:41 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

static void	zero_map_struct(t_map *map)
{
	map->fd = 0;
	map->mlx = NULL;
	map->y = 0;
	map->x = 0;
	map->max_y = 0;
	map->max_x = 0;
	map->plr_y = 0;
	map->plr_x = 0;
	map->str = NULL;
	map->arr = NULL;
	map->images = NULL;
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
	for (int i = 0; map.arr[i]; i++)
		printf("%s\n", map.arr[i]);
	//mlx_set_setting(MLX_STRETCH_IMAGE, true);
	map.mlx = mlx_init((map.max_x + 1) * WIDTH, (map.max_y + 1) * HEIGHT,
			"cub3d", true);
	if (!map.mlx)
		struct_error((char *)mlx_strerror(mlx_errno), &map);
	//display_map(&map);
	//mlx_key_hook(map.mlx, &wasd_keyhook, &map);
	mlx_loop(map.mlx);
	free_map_struct(map);
	mlx_terminate(map.mlx);
	//zero_map_struct(&map);
	return (0);
}
