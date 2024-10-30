/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:42:21 by emichels          #+#    #+#             */
/*   Updated: 2024/10/30 10:56:51 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

void	generate_map(char map[MH][MW])
{
	const char	directions[] = {'N', 'S', 'E', 'W'};
	const char	elements[] = {'0', '1'};
	t_player	p;
	int			i;
	int			j;

	i = -1;
	while (++i < MH)
	{
		j = -1;
		while (++j < MW)
		{
			if (i == 0 || i == MH - 1 || j == 0 || j == MW - 1)
				map[i][j] = '1';
			else
				map[i][j] = elements[rand() % 2];
		}
	}
	p.player_x = rand() % (MW - 2) + 1;
	p.player_y = rand() % (MH - 2) + 1;
	p.player_direction = directions[rand() % 4];
	map[p.player_y][p.player_x] = p.player_direction;
}

void	print_map(char map[MH][MW])
{
	FILE	*file;
	int		i;
	int		j;

	file = fopen("../maps/rand_map.cub", "w");
	if (file == NULL)
	{
		printf("Error opening map file.\n");
		return ;
	}
	i = -1;
	while (++i < MH)
	{
		j = -1;
		while (++j < MW)
			fputc(map[i][j], file);
		fputc('\n', file);
	}
	fclose(file);
}

int	main(void)
{
	char	map[MH][MW];

	srand(time(NULL));
	generate_map(map);
	print_map(map);
	return (0);
}
