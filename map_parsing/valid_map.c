/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:51:12 by emichels          #+#    #+#             */
/*   Updated: 2024/11/29 11:16:09 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	is_walled(t_map *map)
{
	int	len;

	map->y = 0;
	while (map->y <= map->max_y)
	{
		map->x = 0;
		len = ft_strlen(map->arr[map->y]);
		while (map->arr[map->y][map->x])
		{
			if (map->y == 0)
				first_line(map);
			if (map->y == map->max_y)
				last_line(map);
			if (map->y > 0 && map->y < map->max_y)
				middle_map(map, len);
			map->x++;
		}
		map->y++;
	}
}

static void	search_unfilled(char **map_arr, t_map *cur)
{
	int	i;
	int	k;

	k = 1;
	i = 1;
	while (k < cur->max_y)
	{
		i = 1;
		while (map_arr[k][i] && i < cur->max_x)
		{
			if (map_arr[k][i] == 'x')
			{
				if (map_arr[k][i + 1] != 'x' && map_arr[k][i + 1] != '1')
					traverse_path(map_arr, cur, k, i + 1);
				else if (map_arr[k][i - 1] != 'x' && map_arr[k][i - 1] != '1')
					traverse_path(map_arr, cur, k, i - 1);
				else if (map_arr[k + 1][i] != 'x' && map_arr[k + 1][i] != '1')
					traverse_path(map_arr, cur, k + 1, i);
				else if (map_arr[k - 1][i] != 'x' && map_arr[k - 1][i] != '1')
					traverse_path(map_arr, cur, k - 1, i);
			}
			i++;
		}
		k++;
	}
}

void	traverse_path(char **arr, t_map *cur, int y, int x)
{
	if (y < 1 || x < 1 || y > cur->max_y || x > cur->max_x
		|| arr[y][x] == 'x' || arr[y][x] == '1')
		return ;
	arr[y][x] = 'x';
	traverse_path(arr, cur, y, x - 1);
	traverse_path(arr, cur, y, x + 1);
	traverse_path(arr, cur, y - 1, x);
	traverse_path(arr, cur, y + 1, x);
	search_unfilled(arr, cur);
}

static void	valid_path(t_map *p)
{
	int		found;

	found = 0;
	p->y = 1;
	while (p->y < p->max_y)
	{
		p->x = 1;
		while (p->arr[p->y][p->x])
		{
			if (p->arr[p->y][p->x] == 'N' || p->arr[p->y][p->x] == 'S'
				|| p->arr[p->y][p->x] == 'E' || p->arr[p->y][p->x] == 'W')
			{
				p->plr_y = p->y;
				p->plr_x = p->x;
				found = 1;
				break ;
			}
			p->x++;
		}
		if (found)
			break ;
		p->y++;
	}
	traverse_path(p->arr, p, p->y, p->x);
}

void	is_valid(t_map *map)
{
	map->arr = ft_split(map->str, '\n');
	if (!map->arr)
		struct_error("Error\nmap has empty line\n", map);
	map->y = 0;
	is_walled(map);
	valid_path(map);
	ft_free(map->arr);
	map->arr = NULL;
}
