/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycaster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:19:15 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/03 13:21:03 by wxuerui          ###   ########.fr       */
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

void	init_render_option(t_render_option *render_opt)
{
	render_opt->fisheye = 0;
	render_opt->minimap = 1;
	render_opt->using_mouse = 0;
	render_opt->times_to_rotate_horz = 0;
	render_opt->mouse_rotate_speed = 0;
}
