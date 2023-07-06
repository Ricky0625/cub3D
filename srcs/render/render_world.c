/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:07:32 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/05 18:19:54 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Get the height of the slice.
 * 
 * @param ray the ray struct (each individual ray)
 * @param proj_attr the projection attribute struct
 * 
 * @return double the height of the slice
 * 
 * @details
 * Below is the formula of the slice height:
 * 
 *  slice height     texture height
 * -------------- = ----------------
 *  dist to plane     dist of ray
 * 
 * Simplify the formula:
 * 
 * slice height = (texture height / dist of ray) / dist to plane
*/
static double	get_slice_height(t_ray *ray, t_projection_attr *proj_attr)
{
	double	slice_height;

	slice_height = (GRID_SIZE / ray->dist) * proj_attr->dist_to_plane;
	return (slice_height);
}

/**
 * @brief Setup everything that needed to draw the slice.
 * 
 * @param cub the main struct
 * @param ray the ray struct (each individual ray)
 * @param col_index the index of the column (y-axis)
 * 
 * @return t_slice the slice struct (each individual slice)
 * 
 * @details
 * 0. Get the height of the slice.
 * 1. Determine which texture to use for the wall.
 * 2. Determine the offset of the texture. Offset is basically the starting
 *    pixel to copy from the texture.
 * 3. Calculate the starting & ending row where the pixel should copy to.
 * 4. Calculate the step of the texture. Step is basically the number of pixels
 *    to skip/repeat when copying the texture.
*/
static t_slice	setup_slice(t_cub *cub, t_ray *ray)
{
	t_slice				slice;
	t_vector			center;
	t_projection_attr	*proj_attr;
	int					center_offset;

	center = cub->proj_attr.center_pos;
	center_offset = cub->proj_attr.center_offset;
	proj_attr = &cub->proj_attr;
	slice.height = get_slice_height(ray, proj_attr);
	get_wall_texture(cub, ray, &slice);
	get_tex_offset(ray, &slice);
	slice.des_start_y = (center.x - (int)(slice.height / 2)) + center_offset;
	slice.des_end_y = (int)(slice.des_start_y + slice.height);
	slice.tex_step = slice.texture->size.y / get_slice_height(ray, proj_attr);
	return (slice);
}

/**
 * @brief Draw the slice.
 * 
 * @attention
 * A slice is defined as a vertical line of pixels. This comprises of the
 * pixels for ceiling, wall, and floor.
*/
static void	draw_slice(t_cub *cub, t_slice *slice, int col_index)
{
	t_img		*texture;
	int			*texture_data;
	int			pixel;
	double		texture_start;

	texture = slice->texture;
	texture_data = (int *)texture->data;
	texture_start = 0;
	if (slice->des_start_y < 0)
	{
		texture_start = -slice->des_start_y * slice->tex_step;
		slice->des_start_y = 0;
	}
	while (slice->des_start_y < slice->des_end_y
		&& slice->des_start_y < WIN_HEIGHT)
	{
		if (slice->des_start_y >= 0 && slice->des_start_y < WIN_HEIGHT)
		{
			pixel = texture_data[(int)texture_start
				* (texture->line_size / 4) + (int)slice->offset];
			draw_pixel(&cub->buffer, col_index, slice->des_start_y, pixel);
		}
		slice->des_start_y++;
		texture_start += slice->tex_step;
	}
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
		slice = setup_slice(cub, ray);
		if (slice.des_start_y > 0)
			draw_vertical_line(cub, (t_vector){col_index, 0},
				slice.des_start_y, cub->textures.ceil);
		draw_slice(cub, &slice, col_index);
		if (slice.des_end_y < WIN_HEIGHT)
			draw_vertical_line(cub, (t_vector){col_index, slice.des_end_y},
				WIN_HEIGHT - 1 - slice.des_end_y, cub->textures.floor);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->buffer.ref, 0, 0);
}
