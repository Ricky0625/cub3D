/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:06:53 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/23 15:50:24 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adjust_fov(t_cub *cub, int key)
{
	int					new_fov;
	t_projection_attr	*proj_attr;

	new_fov = cub->proj_attr.fov;
	proj_attr = &cub->proj_attr;
	if ((key == KEY_PLUS && proj_attr->fov == FOV_MAX)
		|| (key == KEY_MINUS && proj_attr->fov == FOV_MIN))
		return ;
	if (key == KEY_PLUS && proj_attr->fov < FOV_MAX)
		new_fov += FOV_STEP;
	else if (key == KEY_MINUS && proj_attr->fov > FOV_MIN)
		new_fov -= FOV_STEP;
	proj_attr->fov = new_fov;
	proj_attr->dist_to_proj_plane = (WIN_WIDTH / 2) / tan(deg_to_rad(FOV / 2));
	proj_attr->ray_angle_step = deg_to_rad((double)new_fov / WIN_WIDTH);
}

void	change_raycasting_option(t_cub *cub, int key)
{
	if (key == KEY_F)
		cub->render_opt.fisheye = !cub->render_opt.fisheye;
	else if (key == KEY_M)
		cub->render_opt.minimap = !cub->render_opt.minimap;
}

void	adjust_center_offset(t_cub *cub, int key)
{
	t_projection_attr	*proj_attr;

	proj_attr = &cub->proj_attr;
	if ((key == KEY_Q && proj_attr->center_offset == CENTER_OFFSET_MAX)
		|| (key == KEY_E && proj_attr->center_offset == -CENTER_OFFSET_MAX))
		return ;
	if (key == KEY_Q && proj_attr->center_offset < CENTER_OFFSET_MAX)
		proj_attr->center_offset += CENTER_OFFSET_STEP;
	else if (key == KEY_E && proj_attr->center_offset > -CENTER_OFFSET_MAX)
		proj_attr->center_offset -= CENTER_OFFSET_STEP;
}

void	reset_raycasting_environment(t_cub *cub)
{
	init_projection_attribute(&cub->proj_attr);
	init_render_option(&cub->render_opt);
}
