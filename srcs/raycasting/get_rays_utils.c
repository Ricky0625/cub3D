/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rays_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:26:20 by wxuerui           #+#    #+#             */
/*   Updated: 2023/06/27 15:05:14 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_cub *cub, t_vector p)
{
	char	**map;

	map = cub->map.map;
	if (p.y < 0 || p.x < 0
		|| !map[p.y / GRID_SIZE]
		|| p.x / GRID_SIZE >= (int)ft_strlen(map[p.y / GRID_SIZE]))
		return (0);
	if (map[p.y / GRID_SIZE][p.x / GRID_SIZE] == '1')
		return (1);
	// if (map[(p.y + 1) / GRID_SIZE]
	// 	&& (p.x + 1) / GRID_SIZE < (int)ft_strlen(map[(p.y + 1) / GRID_SIZE]))
	// 	if (map[(p.y + 1) / GRID_SIZE][(p.x + 1) / GRID_SIZE] == '1')
	// 		return (1);
	// if (map[(p.y + 1) / GRID_SIZE] && p.x > 0)
	// 	if (map[(p.y + 1) / GRID_SIZE][(p.x - 1) / GRID_SIZE] == '1')
	// 		return (1);
	// if (p.y > 0
	// 	&& (p.x + 1) / GRID_SIZE < (int)ft_strlen(map[(p.y - 1) / GRID_SIZE]))
	// 	if (map[(p.y - 1) / GRID_SIZE][(p.x + 1) / GRID_SIZE] == '1')
	// 		return (1);
	// if (p.y > 0 && p.x > 0)
	// 	if (map[(p.y - 1) / GRID_SIZE][(p.x - 1) / GRID_SIZE] == '1')
	// 		return (1);
	return (0);
}

int	dda(t_cub *cub, t_vector_d *p, t_vector_d displacement)
{
	t_vector	temp_p;

	while (1)
	{
		if (p->x < 0 || p->x >= cub->map.size.x * GRID_SIZE)
			return (0);
		if (p->y < 0 || p->y >= cub->map.size.y * GRID_SIZE)
			return (0);
		temp_p.x = p->x;
		temp_p.y = p->y;
		if (is_wall(cub, temp_p))
			return (1);
		p->x += displacement.x;
		p->y += displacement.y;
	}
}
