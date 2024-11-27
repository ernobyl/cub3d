/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color_specs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:47:41 by emichels          #+#    #+#             */
/*   Updated: 2024/11/27 12:14:56 by msilfver         ###   ########.fr       */
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
	r = atoi_cub(line + i);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ',')
		i++;
	g = atoi_cub(line + i);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ',')
		i++;
	b = atoi_cub(line + i);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != '\n')
		struct_error("Error\nInvalid color values\n", map);
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

	while (map->str[i] && map->str[i] != ' ')
		i++;
	while (map->str[i] != '.' && map->str[i])
	{	
		if (map->str[i] != ' ')
			struct_error("Error\nInvalid texture identifier\n", map);
		i++;
	}
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
int	map_set_no_so(t_map *map, int i)
{
	if (ft_strncmp(map->str + i, "NO ", 3) == 0)
	{	
		if (map->textures->no)
			struct_error("Error\nduplicate textures\n", map);
		else
		{
			i = set_texture_wall(map, &map->textures->wall_no, i);
			map->textures->no = 1;
			map->element_counter++;
		}
	}
	if (ft_strncmp(map->str + i, "SO ", 3) == 0)
	{	
		if (map->textures->so)
			struct_error("Error\nduplicate textures\n", map);
		else
		{
			i = set_texture_wall(map, &map->textures->wall_so, i);
			map->textures->so = 1;
			map->element_counter++;
		}
	}
	return (i);
}

int	map_set_we_ea(t_map *map, int i)
{
	if (ft_strncmp(map->str + i, "WE ", 3) == 0)
	{	
		if (map->textures->we)
			struct_error("Error\nduplicate textures\n", map);
		else
		{
			i = set_texture_wall(map, &map->textures->wall_we, i);
			map->textures->we = 1;
			map->element_counter++;
		}
	}
	if (ft_strncmp(map->str + i, "EA ", 3) == 0)
	{	
		if (map->textures->ea)
			struct_error("Error\nduplicate textures\n", map);
		else
		{
			i = set_texture_wall(map, &map->textures->wall_ea, i);
			map->textures->ea = 1;
			map->element_counter++;
		}
	}
	return (i);
}
int	map_set_texture(t_map *map, int i)
{
	if (ft_strncmp(map->str + i, "NO ", 3) == 0
			|| ft_strncmp(map->str + i, "SO ", 3) == 0)
		i = map_set_no_so(map, i);

	else if (ft_strncmp(map->str + i, "WE ", 3) == 0
			|| ft_strncmp(map->str + i, "EA ", 3) == 0)
		i = map_set_we_ea(map, i);
	return (i);
}

void	map_set_floorcolor(t_map *map, int i)
{
	if (map->images->f_flag == 1)
				struct_error("Error\nMultiple floor colors\n", map);
	map_set_color(map, map->str, i + 1, &map->images->color_floor);
	map->images->f_flag = 1;
	map->element_counter++;
}

void	map_set_ceilingcolor(t_map *map, int i)
{
	if (map->images->c_flag == 1)
				struct_error("Error\nMultiple ceiling colors\n", map);
	map_set_color(map, map->str, i + 1, &map->images->color_ceiling);
	map->images->c_flag = 1;
	map->element_counter++;
}

int	read_color_info_lines(t_map *map, int i)
{
	while (map->str[i])
	{
		i = map_set_texture(map, i);
		if (map->str[i] == 'F')
		{
			map_set_floorcolor(map, i);
			while (map->str[i] != '\n' && map->str[i])
				i++;
		}
		else if (map->str[i] == 'C')
		{
			map_set_ceilingcolor(map, i);
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
	printf("element no: %i\n", map->element_counter);
	if (map->element_counter != 6)
		struct_error("Error\nMissing elements\n", map);
	return (i);
}
