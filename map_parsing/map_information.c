/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_information.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:18:10 by emichels          #+#    #+#             */
/*   Updated: 2024/09/23 12:31:49 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_map_limits(t_map *map)
{
	int		x;
	int		y;

	x = 0;
	while (map->str[x + 1] != '\n')
		x++;
	map->max_x = x;
	y = 0;
	x = 0;
	while (map->str[x + 1] != '\0')
	{
		if (map->str[x] == '\n')
		{
			if (map->str[x + 1] == '\n')
				struct_error("Error\nmap has empty line\n", map);
			y++;
		}
		x++;
	}
	map->max_y = y;
	if (map->max_x < 2 || map->max_y < 2)
		struct_error("Error\nempty line or invalid map dimensions\n", map);
}

void	is_valid_character(t_map *map)
{
	int	i;
	int	duplicate;

	i = 0;
	duplicate = 0;
	while (map->str[i])
	{
		if (map->str[i] != '\n' && map->str[i] != '1' && map->str[i] != '0'
			&& map->str[i] != 'N' && map->str[i] != 'S' && map->str[i] != 'E'
			&& map->str[i] != 'W')
			struct_error("Error\nmap contains invalid character\n", map);
		if (map->str[i] == 'N' || map->str[i] == 'S' || map->str[i] == 'E'
			|| map->str[i] == 'W')
			duplicate++;
		if (duplicate > 2)
			struct_error("Error\nduplicate start positions\n", map);
		i++;
	}
	// if (!ft_strchr(map->str, '1') || !ft_strchr(map->str, 'N')
	// 	|| !ft_strchr(map->str, 'S') || !ft_strchr(map->str, 'E')
	// 	|| !ft_strchr(map->str, 'W'))
	// 	struct_error("Error\nmap elements missing\n", map);
}
