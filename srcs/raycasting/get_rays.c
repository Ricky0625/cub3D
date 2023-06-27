/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:11:42 by wxuerui           #+#    #+#             */
/*   Updated: 2023/06/27 14:37:46 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	check_by_horizontal_intersections(t_cub *cub, double angle)
{
	t_vector_d	displacement;
	t_vector	pos;
	t_vector_d	p;

	pos = cub->player.unit_pos;
	// face down by default
	displacement.x = -(GRID_SIZE / tan(angle));
	displacement.y = GRID_SIZE;
	p.y = (pos.y / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
	if (angle < M_PI) // face up
	{
		displacement.x = -displacement.x;
		p.y = (pos.y / GRID_SIZE) * GRID_SIZE - 1;
		displacement.y = -GRID_SIZE;
	}
	p.x = pos.x + (pos.y - p.y) / tan(angle);
	if (dda(cub, &p, displacement) == 0)
		return ((t_vector){-42, -42});
	return ((t_vector){p.x, p.y});
}

t_vector	check_by_vertical_intersections(t_cub *cub, double angle)
{
	t_vector_d	displacement;
	t_vector	pos;
	t_vector_d	p;

	pos = cub->player.unit_pos;
	// face right by default
	displacement.x = GRID_SIZE;
	displacement.y = -(GRID_SIZE * tan(angle));
	p.x = (pos.x / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
	if (angle > M_PI_2 && angle < M_PI_2 * 3) // face left
	{
		displacement.y = -displacement.y;
		p.x = (pos.x / GRID_SIZE) * GRID_SIZE - 1;
		displacement.x = -GRID_SIZE;
	}
	p.y = pos.y + ((pos.x - p.x) * tan(angle));
	if (dda(cub, &p, displacement) == 0)
		return ((t_vector){-42, -42});
	return ((t_vector){p.x, p.y});
}

t_ray	get_ray(t_cub *cub, double angle)
{
	t_vector	by_x;
	t_vector	by_y;
	double		dists[2];

	if (angle < 0)
		angle += M_PI * 2;
	else if (angle >= M_PI * 2)
		angle -= M_PI * 2;
	by_x = check_by_horizontal_intersections(cub, angle);
	by_y = check_by_vertical_intersections(cub, angle);
	dists[0] = get_distance((t_vector_d){cub->player.unit_pos.x, cub->player.unit_pos.y}, (t_vector_d){by_x.x, by_x.y});
	dists[1] = get_distance((t_vector_d){cub->player.unit_pos.x, cub->player.unit_pos.y}, (t_vector_d){by_y.x, by_y.y});
	if (by_y.x == -42 && by_y.y == -42)
		return ((t_ray){by_x, dists[0], angle});
	else if (by_x.x == -42 && by_x.y == -42)
		return ((t_ray){by_y, dists[1], angle});
	if (dists[0] < dists[1])
		return ((t_ray){by_x, dists[0], angle});
	return ((t_ray){by_y, dists[1], angle});
}

void	store_rays_to_cub(t_cub *cub)
{
	int		i;
	int		fov;
	double	cast_angle;
	t_ray	ray;

	i = -1;
	fov = cub->proj_attr.fov;
	cast_angle = cub->player.viewing_angle + deg_to_rad(fov) / 2;
	while (++i < WIN_WIDTH)
	{
		ray = get_ray(cub, cast_angle);
		if (cub->render_opt.fisheye == 0)
			ray.dist *= cos(cub->player.viewing_angle - cast_angle);
		cub->rays[i] = ray;
		cast_angle -= cub->proj_attr.ray_angle_step;
	}
}
