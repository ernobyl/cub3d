/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_spec_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilfver <msilfver@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:33:34 by emichels          #+#    #+#             */
/*   Updated: 2024/12/02 12:14:28 by msilfver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	map_set_floorcolor(t_map *map, int i)
{
	if (map->images->f_flag == 1)
		struct_error("Error\nMultiple floor colors\n", map);
	map_set_color(map, map->str, i + 1, &map->images->color_floor);
	map->images->f_flag = 1;
	map->element_counter++;
	while (map->str[i] != '\n' && map->str[i])
		i++;
	return (i);
}

int	map_set_ceilingcolor(t_map *map, int i)
{
	if (map->images->c_flag == 1)
		struct_error("Error\nMultiple ceiling colors\n", map);
	map_set_color(map, map->str, i + 1, &map->images->color_ceiling);
	map->images->c_flag = 1;
	map->element_counter++;
	while (map->str[i] != '\n' && map->str[i])
		i++;
	return (i);
}
