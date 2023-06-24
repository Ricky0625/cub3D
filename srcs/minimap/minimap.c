/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wangxuerui2003@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:19:55 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/24 11:58:52 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Render the background map
 * If at '1', draw wall color.
 * else if at ' ', draw void color.
 * else ('0', player), draw floor color;
*/
void	mm_render_background(t_cub *cub, char **map, t_vector size)
{
	int	x;
	int	y;

	y = -1;
	ft_bzero(cub->buffer.data, WIN_WIDTH * WIN_HEIGHT);
	while (++y < MM_TILE_SIZE * size.y)
	{
		x = -1;
		while (++x < MM_TILE_SIZE * (int)ft_strlen(map[y / MM_TILE_SIZE]))
		{
			if (map[y / MM_TILE_SIZE][x / MM_TILE_SIZE] == '1')
				draw_pixel(cub, x, y, MM_COLOR_WALL);
			else if (map[y / MM_TILE_SIZE][x / MM_TILE_SIZE] == ' ')
				draw_pixel(cub, x, y, MM_COLOR_VOID);
			else
				draw_pixel(cub, x, y, MM_COLOR_FLOOR);
		}
	}
}

/**
 * Draw the player triangle on the minimap with scale.
 * 
 * Player is a isosceles triangle, not equilateral,
 * that's why some divide by 2 and some by 3.
 * 
 * Hint: M_PI / 1.5 is 120 deg
*/
void	mm_put_player(t_cub *cub, t_player *player, double scale)
{
	t_vector	vertices[3];
	int			x;
	int			y;

	x = player->unit_pos.x;
	y = player->unit_pos.y;
	vertices[0].x = roundf(x * scale
			+ cos(player->viewing_angle) * MM_TILE_SIZE / 2);
	vertices[0].y = roundf(y * scale
			+ -sin(player->viewing_angle) * MM_TILE_SIZE / 2);
	vertices[1].x = roundf(x * scale
			+ cos(player->viewing_angle + M_PI / 1.5) * MM_TILE_SIZE / 3);
	vertices[1].y = roundf(y * scale
			+ -sin(player->viewing_angle + M_PI / 1.5) * MM_TILE_SIZE / 3);
	vertices[2].x = roundf(x * scale
			+ cos(player->viewing_angle - M_PI / 1.5) * MM_TILE_SIZE / 3);
	vertices[2].y = roundf(y * scale
			+ -sin(player->viewing_angle - M_PI / 1.5) * MM_TILE_SIZE / 3);
	draw_triangle(cub, vertices, MM_COLOR_PLAYER, 1);
}

/**
 * 
*/
void	mm_draw_rays(t_cub *cub, t_player *player, double scale)
{
	t_vector	scaled_player_upos;
	t_vector	scaled_ray_p_inter;
	int			i;

	scaled_player_upos.x = player->unit_pos.x * scale;
	scaled_player_upos.y = player->unit_pos.y * scale;
	i = -1;
	while (++i < WIN_WIDTH)
	{
		scaled_ray_p_inter.x = cub->rays[i].p_intersection.x * scale;
		scaled_ray_p_inter.y = cub->rays[i].p_intersection.y * scale;
		draw_line(cub, scaled_player_upos, scaled_ray_p_inter, MM_COLOR_RAY);
	}
}

void	render_minimap(t_cub *cub)
{
	mm_render_background(cub, cub->map.map, cub->map.size);
	mm_put_player(cub, &cub->player, cub->mm_scale);
	mm_draw_rays(cub, &cub->player, cub->mm_scale);
}
