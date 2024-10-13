/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_information.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:18:10 by emichels          #+#    #+#             */
/*   Updated: 2024/10/13 10:43:35 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* static void	init_arr(t_map *map)
{
	map->arr = ft_calloc(map->max_y, map->max_x);
	if (!map->arr)
		struct_error("Calloc error\n", map);
} */
static char	*replace_tabs(t_map *map, char *new)
{
	int	i;
	int	j;
	int	count;
	
	i = 0;
	j = 0;
	while (map->str[i])
	{
		if (map->str[i] == '\t')
		{
			count = 4;
			while (count--)
				new[j++] = ' ';
		}
		else
		{
			new[j] = map->str[i];
			j++;
		}
		i++;
	}
	free(map->str);
	return (new);
}

void	tabs_to_spaces(t_map *map)
{
	int		i;
	int		tabs;
	char	*new;

	i = 0;
	tabs = 0;
	while (map->str[i])
	{
		if (map->str[i] == '\t')
			tabs++;
		i++;
	}
	new = ft_calloc(i + (tabs * 3) + 1, sizeof(char));
	if (!new)
		struct_error("Calloc error\n", map);
	new = replace_tabs(map, new);
	map->str = new;
}

void	set_map_limits(t_map *map)
{
	int		x;
	int		y;
	int		len;

	x = 0;
	len = 0;
	map->max_x = 0;
	y = 0;
	x = 0;
	while (map->str[x + 1] != '\0')
	{
		if (map->str[x] == '\n')
		{
			if (map->max_x <= len)
				map->max_x = len;
			if (map->str[x + 1] == '\n')
				struct_error("Error\nmap has empty line3\n", map);
			y++;
			len = 0;
		}
		x++;
		len++;
	}
	map->max_y = y;
	if (map->max_x < 2 || map->max_y < 2)
		struct_error("Error\nempty line or invalid map dimensions\n", map);
	//init_arr(map);
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
			&& map->str[i] != 'W' && map->str[i] != ' ' && map->str[i] != '\t')
			struct_error("Error\nmap contains invalid character\n", map);
		if (map->str[i] == 'N' || map->str[i] == 'S' || map->str[i] == 'E'
			|| map->str[i] == 'W')
			duplicate++;
		if (duplicate > 1) // was 2 before
			struct_error("Error\nduplicate start positions\n", map);
		i++;
	}
	if (!ft_strchr(map->str, 'N') && !ft_strchr(map->str, 'S')
		&& !ft_strchr(map->str, 'E') && !ft_strchr(map->str, 'W'))
		struct_error("Error\nmap elements missing\n", map);
}
