/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:11:42 by wxuerui           #+#    #+#             */
/*   Updated: 2023/06/22 18:54:36 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_cub *cub, t_vector p)
{
	if (cub->map.map[p.y / GRID_SIZE][p.x / GRID_SIZE] == '1')
		return (1);
	if (cub->map.map[(p.y + 1) / GRID_SIZE][(p.x + 1) / GRID_SIZE] == '1')
		return (1);
	if (cub->map.map[(p.y + 1) / GRID_SIZE][(p.x - 1) / GRID_SIZE] == '1')
		return (1);
	if (cub->map.map[(p.y - 1) / GRID_SIZE][(p.x + 1) / GRID_SIZE] == '1')
		return (1);
	if (cub->map.map[(p.y - 1) / GRID_SIZE][(p.x - 1) / GRID_SIZE] == '1')
		return (1);
	return 0;
}

t_vector	check_by_horizontal_intersections(t_cub *cub, double offset_angle)
{
	int		xa = roundf(GRID_SIZE / tan(cub->player.viewing_angle + offset_angle));
	int		ya = -GRID_SIZE; // face up
	t_player	*ply = &cub->player;
	t_vector	p;

	if ((double)(ply->viewing_angle + offset_angle) < M_PI) // face up
		p.y = (ply->unit_pos.y / GRID_SIZE) * GRID_SIZE - 1;
	else
	{
		p.y = (ply->unit_pos.y / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
		xa = -xa;
		ya = GRID_SIZE;
	}
	p.x = ply->unit_pos.x + roundf((ply->unit_pos.y - p.y) / tan(ply->viewing_angle + offset_angle));
	while (1)
	{
		if (p.x < 0 || p.x >= cub->map.size.x * GRID_SIZE)
			return (t_vector){0, 0};
		if (p.y < 0 || p.y >= cub->map.size.y * GRID_SIZE)
			return (t_vector){0, 0};
		if (is_wall(cub, p))
			return (p);
		p.x += xa;
		p.y += ya;
	}

	return (p);
}

t_vector	check_by_vertical_intersections(t_cub *cub, double offset_angle)
{
	int		xa = GRID_SIZE; // face right
	int		ya = roundf(GRID_SIZE * tan(cub->player.viewing_angle + offset_angle));
	t_player	*ply = &cub->player;
	t_vector	p;

	if ((double)(ply->viewing_angle + offset_angle) < M_PI_2 || (double)(ply->viewing_angle + offset_angle) > M_PI_2 * 3) // face right
	{
		p.x = (ply->unit_pos.x / GRID_SIZE) * GRID_SIZE + GRID_SIZE;
		ya = -ya;
	}
	else
	{
		p.x = (ply->unit_pos.x / GRID_SIZE) * GRID_SIZE - 1;
		xa = -GRID_SIZE;
	}
	p.y = ply->unit_pos.y + roundf((ply->unit_pos.x - p.x) * tan(ply->viewing_angle + offset_angle));

	while (1)
	{
		if (p.x < 0 || p.x >= cub->map.size.x * GRID_SIZE)
			return (t_vector){0, 0};
		if (p.y < 0 || p.y >= cub->map.size.y * GRID_SIZE)
			return (t_vector){0, 0};
		if (is_wall(cub, p))
			return (p);
		p.x += xa;
		p.y += ya;
	}

	return (p);
}

t_ray	get_ray(t_cub *cub, double offset_angle)
{
	if (cub->player.viewing_angle + offset_angle < 0)
		offset_angle += M_PI * 2;
	else if (cub->player.viewing_angle + offset_angle >= M_PI * 2)
		offset_angle -= M_PI * 2;
	t_vector	by_x = check_by_horizontal_intersections(cub, offset_angle);
	t_vector	by_y = check_by_vertical_intersections(cub, offset_angle);
	// draw_line(cub, cub->player.unit_pos, by_x, 0);
	// draw_line(cub, cub->player.unit_pos, by_y, 0xff0000);
	if (by_x.x == 0 && by_x.y == 0)
		return (t_ray){by_y, get_distance(cub->player.unit_pos, by_y), cub->player.viewing_angle + offset_angle};
	else if (by_y.x == 0 && by_y.y == 0)
		return (t_ray){by_x, get_distance(cub->player.unit_pos, by_x), cub->player.viewing_angle + offset_angle};

	if (get_distance(cub->player.unit_pos, by_x) < get_distance(cub->player.unit_pos, by_y))
		return ((t_ray){by_x, get_distance(cub->player.unit_pos, by_x), cub->player.viewing_angle + offset_angle});
	return ((t_ray){by_y, get_distance(cub->player.unit_pos, by_y), cub->player.viewing_angle + offset_angle});
}

void	store_rays_to_cub(t_cub *cub)
{
	t_ray	ray;
	int		i;

	// 0xbffcc6 ray
	double offset = -M_PI / 6;
	i = -1;
	while (++i < WIN_WIDTH) {
		offset += M_PI / WIN_WIDTH / 3;
		ray = get_ray(cub, offset);
		// draw_line(cub, cub->player.unit_pos, ray, 0xbffcc6);
		cub->rays[i] = ray;
	}
}