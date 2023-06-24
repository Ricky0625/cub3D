/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wangxuerui2003@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:11:09 by wxuerui           #+#    #+#             */
/*   Updated: 2023/06/24 18:38:25 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mm_adjust_start_and_end(t_cub *cub, t_vector *start, t_vector *end)
{
	if (start->x < 0)
	{
		if (end->x + (-start->x) < cub->map.size.x * MM_TILE_SIZE)
			end->x += -start->x;
		else
			end->x = cub->map.size.x * MM_TILE_SIZE;
		start->x = 0;
	}
	if (end->x > cub->map.size.x * MM_TILE_SIZE)
	{
		if (start->x - (end->x - cub->map.size.x * MM_TILE_SIZE) >= 0)
			start->x -= (end->x - cub->map.size.x * MM_TILE_SIZE);
		else
			start->x = 0;
		end->x = cub->map.size.x * MM_TILE_SIZE;
	}
	if (start->y < 0)
	{
		if (end->y + (-start->y) <= cub->map.size.y * MM_TILE_SIZE)
			end->y += -start->y;
		else
			end->y = cub->map.size.y * MM_TILE_SIZE;
		start->y = 0;
	}
	if (end->y > cub->map.size.y * MM_TILE_SIZE)
	{
		if (start->y - (end->y - cub->map.size.y * MM_TILE_SIZE) >= 0)
			start->y -= end->y - cub->map.size.y * MM_TILE_SIZE;
		else
			start->y = 0;
		end->y = cub->map.size.y * MM_TILE_SIZE;
	}
}

void	mm_draw_ray(t_cub *cub, t_vector p1, t_vector p2, int color)
{
	t_vector	dir;
	t_vector	delta;
	int			error[2];

	delta.x = int_abs(p2.x - p1.x);
	delta.y = -int_abs(p2.y - p1.y);
	dir.x = -1 + (2 * (p2.x >= p1.x));
	dir.y = -1 + (2 * (p2.y >= p1.y));
	error[0] = delta.x + delta.y;
	while (p1.x != p2.x || p1.y != p2.y)
	{
		if (p1.x >= MM_SIZE * MM_TILE_SIZE || p1.y >= MM_SIZE * MM_TILE_SIZE)
			return ;
		draw_pixel(cub, p1.x, p1.y, color);
		brehensam_algo(&p1, delta, dir, error);
	}
}