/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:31:16 by emichels          #+#    #+#             */
/*   Updated: 2024/09/23 12:07:20 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	valid_extension(char *str)
{
	int		i;
	int		k;
	char	*ext;

	i = 0;
	ext = ".cub";
	while (str[i++])
	{
		if (str[i] == '.')
			break ;
		else if (str[i + 1] == '\0')
			simple_error("Error\ninvalid map format/name\n");
	}
	k = 0;
	while (str[i])
	{
		if (str[i] != ext[k] || k == i)
			simple_error("Error\ninvalid map format/name\n");
		i++;
		k++;
	}
}

static char	*copy_from_file(int fd, char *buf, char *tmp, char *map_str)
{
	int	len;

	len = 1;
	while (len > 0)
	{
		len = read(fd, buf, BUFFERSIZE);
		if (len <= 0)
			free (buf);
		if (len == 0)
			return (map_str);
		if (len < 0)
		{
			free (buf);
			return (NULL);
		}
		buf[len] = '\0';
		tmp = map_str;
		map_str = ft_strjoin(map_str, buf);
		free(tmp);
	}
	return (map_str);
}

void	read_map(t_map *map)
{
	char	*buf;
	char	*tmp;

	tmp = NULL;
	map->str = ft_calloc(1, 1);
	if (!map->str)
		struct_error("Error\nmalloc failed\n", NULL);
	buf = malloc(BUFFERSIZE + 1);
	if (!buf)
	{
		free(map->str);
		struct_error("Error\nmalloc failed\n", NULL);
	}
	map->str = copy_from_file(map->fd, buf, tmp, map->str);
	close(map->fd);
}
