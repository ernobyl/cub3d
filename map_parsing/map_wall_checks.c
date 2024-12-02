/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wall_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:00:38 by emichels          #+#    #+#             */
/*   Updated: 2024/12/02 12:42:30 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	last_line(t_map *map)
{
	if (map->arr[map->y][map->x] == '0')
		struct_error("Error\nmap not walled\n", map);
	if (map->arr[map->y][map->x] == 'N')
		struct_error("Error\nmap not walled\n", map);
	if (map->arr[map->y][map->x] == 'S')
		struct_error("Error\nmap not walled\n", map);
	if (map->arr[map->y][map->x] == 'W')
		struct_error("Error\nmap not walled\n", map);
	if (map->arr[map->y][map->x] == 'E')
		struct_error("Error\nmap not walled\n", map);
}

void	first_line(t_map *map)
{
	if (map->arr[map->y][map->x] == '0')
		struct_error("Error\nmap not walled\n", map);
	if (map->arr[map->y][map->x] == 'N')
		struct_error("Error\nmap not walled\n", map);
	if (map->arr[map->y][map->x] == 'S')
		struct_error("Error\nmap not walled\n", map);
	if (map->arr[map->y][map->x] == 'W')
		struct_error("Error\nmap not walled\n", map);
	if (map->arr[map->y][map->x] == 'E')
		struct_error("Error\nmap not walled\n", map);
}

void	middle_map(t_map *map, int len)
{
	if (map->arr[map->y][map->x] == ' '
		&& map->arr[map->y][map->x + 1] == '0')
		struct_error("Error\nmap not walled\n", map);
	if (map->arr[map->y][map->x] == ' '
		&& map->arr[map->y][map->x - 1] == '0')
		struct_error("Error\nmap not walled\n", map);
	if (map->arr[map->y][map->x] == '0'
		&& (map->x >= (int)ft_strlen(map->arr[map->y + 1])
		|| map->x >= (int)ft_strlen(map->arr[map->y - 1])))
		struct_error("Error\nmap not walled\n", map);
	if (map->x == 0 || map->x == len - 1)
	{
		if (map->arr[map->y][map->x] == '0')
			struct_error("Error\nmap not walled\n", map);
		if (map->arr[map->y][map->x] == 'N')
			struct_error("Error\nmap not walled\n", map);
		if (map->arr[map->y][map->x] == 'S')
			struct_error("Error\nmap not walled\n", map);
		if (map->arr[map->y][map->x] == 'W')
			struct_error("Error\nmap not walled\n", map);
		if (map->arr[map->y][map->x] == 'E')
			struct_error("Error\nmap not walled\n", map);
	}
}
