/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycaster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:19:15 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/06 14:06:58 by wxuerui          ###   ########.fr       */
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
 * 3. Set fov (this fov is in degree)
 * 4. Set fisheye to 0 (this is used to toggle fisheye effect)
 * 5. Set center offset to 0 (use for look up and down)
 * 
 * NOTE: The values of this function will be the default values
*/
void	init_projection_attribute(t_projection_attr *proj_attr)
{
	proj_attr->dist_to_plane = (WIN_WIDTH / 2) / tan(deg_to_rad(FOV / 2));
	proj_attr->ray_angle_step = deg_to_rad((double)FOV / WIN_WIDTH);
	proj_attr->fov = FOV;
	proj_attr->center_offset = 0;
	proj_attr->center_pos = (t_vector){WIN_HEIGHT / 2, WIN_WIDTH / 2};
	proj_attr->mm_scale = (double)MM_TILE_SIZE / GRID_SIZE;
}

/**
 * @brief Setup render options
 * 
 * @param render_opt Pointer to render options struct
 * 
 * @details
 * Set all the render options to their default values
*/
void	init_render_option(t_render_option *render_opt)
{
	render_opt->fisheye = 0;
	render_opt->minimap = 1;
	render_opt->using_mouse = 0;
	render_opt->manual = 0;
	render_opt->mouse_rotate_speed = 0;
	render_opt->animation_index = -1;
}

/**
 * @brief Initialize all the required images
 * 
 * @param cub the main struct
 * 
 * @details
 * Below are the images that will be initialized:
 * 1. Buffer - The main image that will be used to render our world
 * 2. Minimap - The minimap image
 * 3. Manual - The manual image. After initialize this image, we will
 * 		   put the manual background color to it
 * 4. Mouse Pointer - The mouse pointer image
*/
void	init_images(t_cub *cub)
{
	new_image(cub, &cub->buffer, (t_vector){WIN_WIDTH, WIN_HEIGHT});
	new_image(cub, &cub->minimap, (t_vector){MM_IMG_SIZE, MM_IMG_SIZE});
	new_image(cub, &cub->manual, (t_vector){MANUAL_WIDTH, WIN_HEIGHT});
	put_color_to_image(&cub->manual, MANUAL_BG_COLOR,
		MANUAL_WIDTH * WIN_HEIGHT);
	xpm_to_image(cub, &cub->mouse_pointer, "assets/mouse_pointer.xpm");
}
