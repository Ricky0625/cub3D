/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:07:32 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/28 21:18:45 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Formula:
 * 
 * Actual slice height / ray distance = slice height / distance to plane
*/
double	get_slice_height(t_ray *ray, t_projection_attr *proj_attr)
{
	double	slice_height;

	slice_height = (GRID_SIZE / ray->dist) * proj_attr->dist_to_plane;
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
// NOTE: now it's just drawing color lines
// void	draw_slice(t_cub *cub, t_slice *slice)
// {
// 	if (slice->height >= WIN_HEIGHT)
// 		printf("slice greater than win height\n");
// 	else
// 	{
// 		draw_line(cub, slice->des_pos, (t_vector){slice->des_pos.x, (WIN_HEIGHT - slice->height) / 2}, cub->textures.ceil);
// 		draw_line(cub, (t_vector){slice->des_pos.x, (WIN_HEIGHT - slice->height) / 2 + slice->height},
// 			(t_vector){slice->des_pos.x, WIN_HEIGHT - 1}, cub->textures.floor);
// 	}
// }

/**
 * NOTE: use NORTH texture for all now
 * 
 * Texture mapping flow:
 * 0. Determine the texture to use. [DONE]
 * 1. Determine the texture offset. [DONE]
 * 2. Determine the texture step. [DONE]
 * 4. Perform texture mapping.
*/

t_slice	setup_slice(t_cub *cub, t_ray *ray, int col_index)
{
	t_slice	slice;

	get_wall_texture(cub, ray, &slice); // assuming all is NORTH texture
	get_tex_offset(ray, &slice, col_index);
	slice.end_pos_y = WIN_HEIGHT - 1; // always end at the bottom of the screen (row) [HARD CODED]
	// y is row, x is col
	slice.des_pos = (t_vector){col_index, 0}; // always start from row 0, no need to times 4 (ARGB) or line size
	slice.height = get_slice_height(ray, &cub->proj_attr);
	slice.tex_step = slice.texture->size.y / get_slice_height(ray, &cub->proj_attr);
	return (slice);
}

void	render_world(t_cub *cub)
{
	int		col_index;
	t_ray	*ray;
	t_slice	slice;

	col_index = -1;
	while (++col_index < WIN_WIDTH)
	{
		ray = &cub->rays[col_index];
		slice = setup_slice(cub, ray, col_index);
		draw_slice(cub, &slice);
		exit(0);
	}
	// exit(0);
}
		// printf("Orientation: %s\n", ray->ray_ortt == HORIZONTAL ? "HORIZONTAL" : (ray->ray_ortt == VERTICAL ? "VERTICAL" : "NONE"));
