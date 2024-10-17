/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_information.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:18:10 by emichels          #+#    #+#             */
/*   Updated: 2024/10/17 16:55:49 by emichels         ###   ########.fr       */
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

void	map_set_color(t_map *map, char *line, int i, uint32_t color)
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
	{
        color = (r << 24) | (g << 16) | (b << 8) | 255;
		printf("r: %i\ng: %i\nb: %i\n", r, g, b);
	}
    else
        struct_error("Invalid color values\n", map);
}

void	map_set_texture(t_map *map, char *path)
{
	// placeholder function
	(void)map;
	printf("%s", path);
}

int	check_line(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
			return (1);
		i++;
	}
	return (0);
}

bool	wall_check(char *str)
{
	if (ft_strchr(str, '1') != NULL)
		return (true);
	else
		return (false);
}

int	map_color_specs(t_map *map)
{
	int	i;

	i = 0;
	while (map->str[i])
	{
		if (ft_strncmp(map->str + i, "NO", 2) == 0 || ft_strncmp(map->str + i, "SO", 2) == 0
			|| ft_strncmp(map->str + i, "WE", 2) == 0 || ft_strncmp(map->str + i, "EA", 2) == 0)
		{
			// set texture (path = from this point until newline);
			map_set_texture(map, "path to texture\n");
			while (map->str[i] != '\n' && map->str[i])
				i++;
		}
		else if (map->str[i] == 'F')
		{	
			map_set_color(map, map->str, i + 1, map->images->color_floor);
			while (map->str[i] != '\n' && map->str[i])
				i++;
		}
		else if (map->str[i] == 'C')
		{	
			map_set_color(map, map->str, i + 1, map->images->color_ceiling);
			while (map->str[i] != '\n' && map->str[i])
				i++;
		}
 		else if (map->str[i] == '\n')
			i++;
		else if (check_line(map->str + i) == 1)
			break;
	}
	// while (map->str[i] == '\n' && check_line(map->str + i) == 0)
	// 	i++;
	return (i);
}

void	set_map_limits(t_map *map)
{
	int		x;
	int		y;
	int		len;
	char	*temp;

	len = 0;
	map->max_x = 0;
	y = 0;
	x = map_color_specs(map); // start from where the color / texture specifications ended
	temp = ft_strdup(map->str + x);
	map->str = temp;
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
