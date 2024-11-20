/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov_object.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emichels <emichels@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:56:50 by emichels          #+#    #+#             */
/*   Updated: 2024/11/20 14:03:23 by emichels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POV_OBJECT_H
# define POV_OBJECT_H

# include "cub3d.h"

typedef struct s_pov
{
	mlx_texture_t	*sprite_frame_1;
	mlx_texture_t	*sprite_frame_2;
	mlx_texture_t	*sprite_frame_3;
	mlx_image_t		*pov_frame1;
	mlx_image_t		*pov_frame2;
	mlx_image_t		*pov_frame3;
}	t_pov;

#endif