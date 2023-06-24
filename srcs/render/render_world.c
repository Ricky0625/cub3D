/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:07:32 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/24 16:42:24 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Flow for rendering world:
 * 
 * 1. Calculate the slice height for each ray. [DONE]
 * 2. The slice height need to plus/minus center offset.
 * 3. Draw the ceiling, slice then floor.
*/

/**
 * Formula:
 * 
 * Actual slice height / ray distance = slice height / distance to plane
*/
int		get_slice_height(t_ray *ray, t_projection_attr *proj_attr)
{
	int	slice_height;

	slice_height = floor((GRID_SIZE / ray->dist) * proj_attr->dist_to_plane);
	return (slice_height);
}

void	render_world(t_cub *cub)
{
	int		col_index;
	t_ray	*ray;

	col_index = -1;
	while (++col_index < WIN_WIDTH)
	{
		ray = &cub->rays[col_index];
	}
}
