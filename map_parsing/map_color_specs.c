/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color_specs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:47:41 by emichels          #+#    #+#             */
/*   Updated: 2024/11/26 10:21:29 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	map_set_color(t_map *map, char *line, int i, uint32_t *color)
{
	int	r;
	int	g;
	int	b;

	while (line[i] == ' ')
		i++;
	r = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ',' || line[i] == ' ')
		i++;
	g = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ',' || line[i] == ' ')
		i++;
	b = ft_atoi(line + i);
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
		*color = (r << 24) | (g << 16) | (b << 8) | 255;
	else
		struct_error("Error\nInvalid color values\n", map);
}

int	set_texture_wall(t_map *map, mlx_texture_t **texture, int i)
{
	int		path_start;
	int		j;
	char	*path;

	while (map->str[i] != '.' && map->str[i])
		i++;
	path_start = i;
	while (map->str[i] != '\n' && map->str[i])
		i++;
	path = ft_calloc(i - path_start + 1, sizeof(char));
	j = 0;
	while (path_start < i)
		path[j++] = map->str[path_start++];
	printf("%s\n", path);
	load_textures(map, texture, path);
	free(path);
	i++;
	return (i);
}

int	map_set_texture(t_map *map, int i)
{
	if (ft_strncmp(map->str + i, "NO ", 3) == 0)
		i = set_texture_wall(map, &map->textures->wall_no, i);
	if (ft_strncmp(map->str + i, "SO ", 3) == 0)
		i = set_texture_wall(map, &map->textures->wall_so, i);
	if (ft_strncmp(map->str + i, "WE ", 3) == 0)
		i = set_texture_wall(map, &map->textures->wall_we, i);
	if (ft_strncmp(map->str + i, "EA ", 3) == 0)
		i = set_texture_wall(map, &map->textures->wall_ea, i);
	return (i);
}

int	read_color_info_lines(t_map *map, int i)
{
	while (map->str[i])
	{
		if (ft_strncmp(map->str + i, "NO ", 3) == 0
			|| ft_strncmp(map->str + i, "SO ", 3) == 0
			|| ft_strncmp(map->str + i, "WE ", 3) == 0
			|| ft_strncmp(map->str + i, "EA ", 3) == 0)
			i = map_set_texture(map, i);
		else if (map->str[i] == 'F')
		{
			map_set_color(map, map->str, i + 1, &map->images->color_floor);
			while (map->str[i] != '\n' && map->str[i])
				i++;
		}
		else if (map->str[i] == 'C')
		{
			map_set_color(map, map->str, i + 1, &map->images->color_ceiling);
			while (map->str[i] != '\n' && map->str[i])
				i++;
		}
		else if (map->str[i] == '\n')
			i++;
		else if (check_line(map->str + i) == 1)
			break ;
	}
	return (i);
}

int	map_color_specs(t_map *map)
{
	int			i;

	alloc_images(map);
	set_default_colors(map);
	i = 0;
	i = read_color_info_lines(map, i);
	return (i);
}
