/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:31:16 by emichels          #+#    #+#             */
/*   Updated: 2024/12/02 15:41:33 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_directory(char *path)
{
	int	fd;
	int	buffer[1];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, buffer, 1) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	correct_path(char *str, int i)
{
	int	j;

	j = i;
	if (i == 0)
		return (-1);
	while (str[j] && j > 0)
	{
		if (str[j] == '/' )
		{
			if (j == i - 1)
				return (-1);
			break ;
		}
		j--;
	}
	return (0);
}

void valid_extension(char *str)
{
    char *ext;
    size_t len;
    size_t ext_len;

	ext = ".cub";
	len = ft_strlen(str);
	ext_len = ft_strlen(ext);
    if (len < ext_len)
        simple_error("Error\ninvalid map format/name\n");
    if (ft_strncmp(str + len - ext_len, ext, ext_len) != 0)
        simple_error("Error\ninvalid map format/name\n");
    if (is_directory(str) == -1 || correct_path(str, len - 4) == -1)
        simple_error("Error\nInvalid file or path\n");
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
