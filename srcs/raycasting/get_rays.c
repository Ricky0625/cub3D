/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:11:42 by wxuerui           #+#    #+#             */
/*   Updated: 2023/06/29 18:44:14 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Check if the ray collides with a horizontal wall.
 * Since every checking of the ray is when it reaches a horizontal boundary,
 * so the displacement Y of the ray casted is either + or - GRID_SIZE.
 * displacement X is 
*/
void	check_by_horizontal_intersections(t_cub *cub, double angle, t_ray *ray)
{
	t_vector_d	displacement;
	t_vector_d	pos;
	t_vector_d	*p;

	p = &ray->p_intersection;
	pos = cub->player.unit_pos;
	displacement.x = -(GRID_SIZE / tan(angle));
	displacement.y = GRID_SIZE;
	ray->door_info = NULL;
	ray->angle = angle;
	ray->ray_ortt = HORIZONTAL;
	p->y = ((int)pos.y / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
	if (angle < M_PI)
	{
		displacement.x = -displacement.x;
		p->y = ((int)pos.y / GRID_SIZE) * GRID_SIZE - 1;
		displacement.y = -GRID_SIZE;
	}
	p->x = pos.x + ((pos.y - p->y) / tan(angle));
	if (dda(cub, p, displacement, ray) == 0)
		ray->dist = INT32_MAX;
	else
		ray->dist = get_distance(cub->player.unit_pos, *p);
}

void	check_by_vertical_intersections(t_cub *cub, double angle, t_ray *ray)
{
	t_vector_d	displacement;
	t_vector_d	pos;
	t_vector_d	*p;

	p = &ray->p_intersection;
	pos = cub->player.unit_pos;
	displacement.x = GRID_SIZE;
	displacement.y = -(GRID_SIZE * tan(angle));
	ray->door_info = NULL;
	ray->ray_ortt = VERTICAL;
	ray->angle = angle;
	p->x = ((int)pos.x / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
	if (angle > M_PI_2 && angle < M_PI_2 * 3)
	{
		displacement.y = -displacement.y;
		p->x = ((int)pos.x / GRID_SIZE) * GRID_SIZE - 1;
		displacement.x = -GRID_SIZE;
	}
	p->y = pos.y + ((pos.x - p->x) * tan(angle));
	if (dda(cub, p, displacement, ray) == 0)
		ray->dist = INT32_MAX;
	else
		ray->dist = get_distance(cub->player.unit_pos, *p);
}

void	get_ray(t_cub *cub, double angle, t_ray *ray)
{
	t_ray	by_x;
	t_ray	by_y;

	if (angle < 0)
		angle += M_PI * 2;
	else if (angle >= M_PI * 2)
		angle -= M_PI * 2;
	check_by_horizontal_intersections(cub, angle, &by_x);
	check_by_vertical_intersections(cub, angle, &by_y);
	if (by_x.dist < by_y.dist)
		*ray = by_x;
	else
		*ray = by_y;
	if (by_x.door_info && by_y.door_info)
	{
		if (by_x.dist < by_y.dist)
			ray->door_info = by_x.door_info;
		else
			ray->door_info = by_y.door_info;
	}
	else if (by_x.door_info)
		ray->door_info = by_x.door_info;
	else if (by_y.door_info)
		ray->door_info = by_y.door_info;
}

void	store_rays_to_cub(t_cub *cub)
{
	int		i;
	int		fov;
	double	cast_angle;

	i = -1;
	fov = cub->proj_attr.fov;
	cast_angle = cub->player.viewing_angle + deg_to_rad(fov) / 2;
	while (++i < WIN_WIDTH)
	{
		get_ray(cub, cast_angle, &cub->rays[i]);
		if (cub->render_opt.fisheye == 0)
			cub->rays[i].dist *= cos(cub->player.viewing_angle - cast_angle);
		cast_angle -= cub->proj_attr.ray_angle_step;
	}
}

/**
 * Ideas for open door:
 * 1. If the door could be found inside the rays of struct,
 * 	  and distance is within x, can open.
 * 2. Press 'E' to open door, and press 'E' again to close door.
*/
