/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycaster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:19:15 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/20 20:44:10 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Setup projection attributes
 * 
 * @param proj_attr Pointer to projection attributes struct
 * 
 * @details
 * 1. Calculate distance to the projection plane (use for scaling)
 * 2. Calculate ray angle step (use to loop from column to column)
*/
void	init_projection_attribute(t_projection_attr *proj_attr)
{
	proj_attr->dist_to_proj_plane = (WIN_WIDTH / 2) / tan(deg_to_rad(FOV / 2));
	proj_attr->ray_angle_step = deg_to_rad((double)FOV / WIN_WIDTH);
}

void	init_step_size(t_vector_d *step_size, double angle, t_step_type type)
{
	if (type == HORIZONTAL)
	{
		step_size->x = GRID_SIZE / tan(angle);
		step_size->y = GRID_SIZE;
	}
	else if (type == VERTICAL)
	{
		step_size->x = GRID_SIZE;
		step_size->y = GRID_SIZE * tan(angle);
	}
}
