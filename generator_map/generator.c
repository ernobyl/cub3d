/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.rgb_vals                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:42:21 by emichels          #+#    #+#             */
/*   Updated: 2024/11/11 19:11:25 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*a;

	a = b;
	while (len--)
		*a++ = c;
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (count * size));
	return (ptr);
}

static int	count_digits(int c)
{
	size_t	len;
	long	mod;

	if (c == 0)
		return (1);
	if (c < 10)
		len = 1;
	else
		len = 0;
	mod = 10;
	while (c % mod != c)
	{
		mod *= 10;
		len++;
	}
	len++;
	return (len);
}

static void	ft_putnbr(char *str, unsigned int n)
{
	size_t	i;

	i = 0;
	if (n < 10)
	{
		while (str[i])
			i++;
		str[i] = n + '0';
	}
	else
	{
		ft_putnbr(str, n / 10);
		ft_putnbr(str, n % 10);
	}
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	char			*result;
	int				len;

	len = count_digits(n) + 1;
	result = (char *)ft_calloc(len, sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		num = -n;
		ft_putnbr(result + 1, num);
	}
	else
	{
		num = n;
		ft_putnbr(result, num);
	}
	return (result);
}

// have to link libft to the generator so everything above this can be removed

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
	t_player	p;
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
		while (++j < MW && map[i][j] != '\0')
			fputc(map[i][j], file);
		fputc('\n', file);
	}
	fclose(file);
}

int	main(void)
{
	char map[MH][MW] = {0};

	srand(time(NULL));
	generate_map(map);
	print_map(map);
	return (0);
}
