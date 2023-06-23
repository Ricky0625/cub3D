/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rays_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wangxuerui2003@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:26:20 by wxuerui           #+#    #+#             */
/*   Updated: 2023/06/23 12:51:03 by wxuerui          ###   ########.fr       */
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
	return (0);
}

int	dda(t_cub *cub, t_vector *p, t_vector displacement)
{
	while (1)
	{
		if (p->x < 0 || p->x >= cub->map.size.x * GRID_SIZE)
			return (0);
		if (p->y < 0 || p->y >= cub->map.size.y * GRID_SIZE)
			return (0);
		if (is_wall(cub, *p))
			return (1);
		p->x += displacement.x;
		p->y += displacement.y;
	}
}
