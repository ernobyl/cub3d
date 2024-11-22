/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:42:21 by emichels          #+#    #+#             */
/*   Updated: 2024/11/22 19:08:32 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_random_ceiling(char map[MH][MW], int k)
{
	int		i;
	int		j;
	int		rgb_vals;
	char	*random;

	i = 0;
	map[k][i++] = 'C';
	map[k][i++] = ' ';
	rgb_vals = 0;
	while (rgb_vals < 3)
	{
		random = ft_itoa(rand() % 256);
		j = 0;
		while (j < 3 && random[j])
		{
			map[k][i] = random[j];
			i++;
			j++;
		}
		free(random);
		if (rgb_vals < 2)
			map[k][i++] = ',';
		rgb_vals++;
	}
	map[k][i] = '\0';
}

void	set_random_floor(char map[MH][MW], int k)
{
	int		i;
	int		j;
	int		rgb_vals;
	char	*random;

	i = 0;
	map[k][i++] = 'F';
	map[k][i++] = ' ';
	rgb_vals = 0;
	while (rgb_vals < 3)
	{
		random = ft_itoa(rand() % 256);
		j = 0;
		while (j < 3 && random[j])
		{
			map[k][i] = random[j];
			i++;
			j++;
		}
		free(random);
		if (rgb_vals < 2)
			map[k][i++] = ',';
		rgb_vals++;
	}
	map[k][i] = '\0';
}

void	generate_map(char map[MH][MW])
{
	const char	directions[] = {'N', 'S', 'E', 'W'};
	const char	elements[] = {'0', '1'};
	t_gen		p;
	int			i;
	int			j;

	set_random_ceiling(map, 0);
	set_random_floor(map, 1);
	i = 1;
	while (++i < MH)
	{
		j = -1;
		while (++j < MW)
		{
			if (i == 2 || i == MH - 1 || j == 0 || j == MW - 1)
				map[i][j] = '1';
			else
				map[i][j] = elements[rand() % 2];
		}
	}
	p.player_x = rand() % (MW - 2) + 1;
	p.player_y = rand() % (MH - 2) + 3;
	p.player_direction = directions[rand() % 4];
	map[p.player_y][p.player_x] = p.player_direction;
}

void	print_map(char map[MH][MW])
{
	FILE	*file;
	int		i;
	int		j;

	file = fopen("./maps/rand_map.cub", "w");
	if (file == NULL)
	{
		printf("Error opening map file.\n");
		return ;
	}
	i = -1;
	while (++i < MH)
	{
		j = -1;
		while (++j < MW && map[i][j] != '\0')
			fputc(map[i][j], file);
		fputc('\n', file);
	}
	fclose(file);
}

void	generator_map(void)
{
	char	map[MH][MW];

	ft_bzero(map, sizeof(map));
	srand(time(NULL));
	generate_map(map);
	print_map(map);
}
