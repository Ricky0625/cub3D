/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_controls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:52:51 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/05 17:56:54 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_door_state(t_door *target_door)
{
	if (target_door == NULL)
		return ;
	if (target_door->state == CLOSED)
		target_door->state = OPEN;
	else if (target_door->state == OPEN)
		target_door->state = CLOSED;
}

void	toggle_door(t_cub *cub)
{
	int			i;
	t_ray		*ray;
	t_door		*door_info;
	t_door		*target_door;
	t_vector_d	door_fov;

	i = -1;
	target_door = NULL;
	door_fov = cub->proj_attr.door_fov;
	while (++i < WIN_WIDTH)
	{
		ray = &cub->rays[i];
		if (ray->angle >= door_fov.x && ray->angle <= door_fov.y
			&& ray->door_info != NULL)
		{
			door_info = ray->door_info;
			if (target_door != NULL && target_door->dist > ray->dist)
				target_door = door_info;
			else if (target_door == NULL
				&& ray->door_info->dist < OPEN_DOOR_DIST)
				target_door = door_info;
		}
	}
	update_door_state(target_door);
}
