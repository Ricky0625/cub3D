/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:06:53 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/03 20:17:52 by wxuerui          ###   ########.fr       */
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
	proj_attr->dist_to_plane = (WIN_WIDTH / 2) / tan(deg_to_rad(FOV / 2));
	proj_attr->ray_angle_step = deg_to_rad((double)new_fov / WIN_WIDTH);
}

void	change_raycasting_option(t_cub *cub, int key)
{
	if (key == KEY_F)
		cub->render_opt.fisheye = !cub->render_opt.fisheye;
	else if (key == KEY_TAB)
		cub->render_opt.minimap = !cub->render_opt.minimap;
	else if (key == KEY_M)
		cub->render_opt.manual = !cub->render_opt.manual;
}

void	adjust_center_offset(t_cub *cub, int key)
{
	t_projection_attr	*proj_attr;

	proj_attr = &cub->proj_attr;
	if ((key == KEY_UP && proj_attr->center_offset >= WIN_HEIGHT / 2)
		|| (key == KEY_DOWN && proj_attr->center_offset <= -WIN_HEIGHT / 2))
		return ;
	if (key == KEY_UP)
		proj_attr->center_offset += CENTER_OFFSET_STEP;
	else if (key == KEY_DOWN)
		proj_attr->center_offset -= CENTER_OFFSET_STEP;
}

void	reset_raycasting_environment(t_cub *cub)
{
	int	old_manual_opt;

	old_manual_opt = cub->render_opt.manual;
	init_projection_attribute(&cub->proj_attr);
	init_render_option(&cub->render_opt);
	cub->render_opt.manual = old_manual_opt;
}

void	toggle_door(t_cub *cub)
{
	int		i;
	t_ray	*ray;
	t_door	*door_info;
	t_door	*target_door;

	i = -1;
	target_door = NULL;
	while (++i < WIN_WIDTH)
	{
		ray = &cub->rays[i];
		if (ray->angle >= cub->proj_attr.door_fov.x && ray->angle <= cub->proj_attr.door_fov.y
			&& ray->door_info != NULL)
		{
			door_info = ray->door_info;
			if (target_door != NULL && target_door->dist > ray->dist)
				target_door = door_info;
			else if (target_door == NULL && ray->door_info->dist < OPEN_DOOR_DIST)
				target_door = door_info;
		}
	}
	if (target_door == NULL)
		return ;
	if (target_door->state == CLOSED)
		target_door->state = OPEN;
	else if (target_door->state == OPEN)
		target_door->state = CLOSED;
}
