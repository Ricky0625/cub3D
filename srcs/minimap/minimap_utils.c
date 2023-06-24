/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wangxuerui2003@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:11:09 by wxuerui           #+#    #+#             */
/*   Updated: 2023/06/24 16:37:38 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adjust_start_and_end(t_cub *cub, t_vector *start, t_vector *end)
{
	if (start->x < 0)
	{
		end->x += -start->x;
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