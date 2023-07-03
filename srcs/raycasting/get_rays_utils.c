/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rays_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:26:20 by wxuerui           #+#    #+#             */
/*   Updated: 2023/06/27 19:27:29 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall_or_door(char **map, t_vector p)
{
	return (
		map[p.y / GRID_SIZE][p.x / GRID_SIZE] == WALL
		|| map[p.y / GRID_SIZE][p.x / GRID_SIZE] == DOOR
	);
}

/**
 * First if the point is out of range, return 0.
 * 
 * Second if the point is right in a wall, return 1.
 * 
 * Third check special case:
 *     if the point is on a corner, either:
 *         map[y + 1][x + 1] and map[y - 1][x - 1] are wall, return 1.
 *         1100
 *         11↙0     For these 2 situations (The arrow is the ray)
 *         0↗11
 *         0011
 * 
 *         map[y + 1][x - 1] and map[y - 1][x + 1] are wall, return 1.
 *         0011
 *         0↘11     For these 2 situations (The arrow is the ray)
 *         11↖0
 *         1100
*/
int	collide(t_cub *cub, t_vector p)
{
	char	**map;

	map = cub->map.map;
	if (p.y < 0 || p.x < 0
		|| !map[p.y / GRID_SIZE])
		return (0);
	if (is_wall_or_door(map, p))
		return (1);
	if ((p.y + 1) / GRID_SIZE < cub->map.size.y && p.y > 0 && p.x > 0)
	{
		if (is_wall_or_door(map, (t_vector){p.x + 1, p.y + 1})
			&& is_wall_or_door(map, (t_vector){p.x - 1, p.y - 1}))
			return (1);
		else if (is_wall_or_door(map, (t_vector){p.x - 1, p.y + 1})
			&& is_wall_or_door(map, (t_vector){p.x + 1, p.y - 1}))
			return (1);
	}
	return (0);
}

int	dda(t_cub *cub, t_vector_d *p, t_vector_d displacement)
{
	while (1)
	{
		if (p->x < 0 || p->x >= cub->map.size.x * GRID_SIZE)
			return (0);
		if (p->y < 0 || p->y >= cub->map.size.y * GRID_SIZE)
			return (0);
		if (collide(cub, (t_vector){p->x, p->y})
			&& collide(cub, (t_vector){ceil(p->x), ceil(p->y)}))
			return (1);
		p->x += displacement.x;
		p->y += displacement.y;
	}
}
