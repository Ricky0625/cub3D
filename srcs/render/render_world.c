/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:07:32 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/24 17:47:28 by wricky-t         ###   ########.fr       */
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

/**
 * Flow for draw slice:
 * 
 * 1. Get slice height.
 * 2. Need to check the height of the slice.
 * 		a. if the slice height is greater than the window height, the whole column will be filled.
 * 		b. if the slice height is less than the window height, the slice will be filled with ceiling, slice then floor.
*/
// NOTE: col_index will be the y-axis
void	draw_slice(t_cub *cub, t_ray *ray, int col_index)
{
	int	slice_height;

	slice_height = get_slice_height(ray, &cub->proj_attr);
	if (slice_height >= WIN_HEIGHT)
		draw_line(cub, (t_vector){col_index, 0}, (t_vector){col_index, WIN_HEIGHT - 1}, cub->textures.ceil);
	else
	{
		// draw_line(cub, (t_vector){col_index, 0}, (t_vector){col_index, (WIN_HEIGHT - slice_height) / 2}, cub->textures.ceil);
		draw_line(cub, (t_vector){col_index, (WIN_HEIGHT - slice_height) / 2}, (t_vector){col_index, (WIN_HEIGHT - slice_height) / 2 + slice_height}, cub->textures.ceil);
		// draw_line(cub, (t_vector){col_index, (WIN_HEIGHT - slice_height) / 2 + slice_height}, (t_vector){col_index, WIN_HEIGHT - 1}, cub->textures.floor);
	}
}

void	render_world(t_cub *cub)
{
	int		col_index;
	t_ray	*ray;

	col_index = -1;
	while (++col_index < WIN_WIDTH)
	{
		ray = &cub->rays[col_index];
		draw_slice(cub, ray, col_index);
	}
}
