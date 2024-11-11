/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:27:12 by emichels          #+#    #+#             */
/*   Updated: 2024/11/11 18:43:19 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERATOR_H
# define GENERATOR_H

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "../libft/libft.h"

# define MW 50  // map width
# define MH 25 // map height

typedef struct s_player
{
	int		player_x;
	int		player_y;
	char	player_direction;
}	t_player;

#endif