/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:42:21 by emichels          #+#    #+#             */
/*   Updated: 2024/09/25 13:53:49 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MW 50  // map width
#define MH 25 // map height

void	generate_map(char map[MH][MW])
{
	const char	directions[] = {'N', 'S', 'E', 'W'};
	const char	elements[] = {'0', '1'};
	for (int i = 0; i < MH; i++)
	{
		for (int j = 0; j < MW; j++)
		{
			if (i == 0 || i == MH - 1 || j == 0 || j == MW - 1)
				map[i][j] = '1';
			else
				map[i][j] = elements[rand() % 2];
		}
	}
	int playerX = rand() % (MW - 2) + 1;
	int playerY = rand() % (MH - 2) + 1;
	char playerDirection = directions[rand() % 4];
	map[playerY][playerX] = playerDirection;
}

void print_map(char map[MH][MW])
{
	FILE *file = fopen("../maps/rand_map.cub", "w");
	if (file == NULL)
	{
		printf("Error opening map file.\n");
		return ;
	}
	for (int i = 0; i < MH; i++)
	{
		for (int j = 0; j < MW; j++)
			fputc(map[i][j], file);
		fputc('\n', file);
	}
	fclose(file);
}

int main(void)
{
	char map[MH][MW];

	srand(time(NULL)); // random seed based on time
	generate_map(map);
	print_map(map);
	return 0;
}
