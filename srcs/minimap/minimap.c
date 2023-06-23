/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wangxuerui2003@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:19:55 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/23 12:35:18 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_minimap(t_cub *cub)
{
	t_vector	player_vertices[3];
	t_player	*player = &cub->player;

	// Render the background map
	for (int y = 0; y < (int)(GRID_SIZE * cub->map.size.y); y++) {
		for (int x = 0; x < (int)(GRID_SIZE * ft_strlen(cub->map.map[y / GRID_SIZE])); x++) {
			if (cub->map.map[y / GRID_SIZE][x / GRID_SIZE] == '0' || ft_strchr(PLY_DIR, cub->map.map[y / GRID_SIZE][x / GRID_SIZE]))
				draw_pixel(cub, x, y, 0xf6f6eb);
			else if (cub->map.map[y / GRID_SIZE][x / GRID_SIZE] == '1')
				draw_pixel(cub, x, y, 0xd5d6ea);
			else
				draw_pixel(cub, x, y, 0);
		}
	}

	// Update player
	player_vertices[0].x = roundf(player->unit_pos.x + cos(player->viewing_angle) * GRID_SIZE / 2);
	player_vertices[0].y = roundf(player->unit_pos.y + -sin(player->viewing_angle) * GRID_SIZE / 2);
	player_vertices[1].x = roundf(player->unit_pos.x + cos(player->viewing_angle + M_PI / 1.5) * GRID_SIZE / 3);
	player_vertices[1].y = roundf(player->unit_pos.y + -sin(player->viewing_angle + M_PI / 1.5) * GRID_SIZE / 3);
	player_vertices[2].x = roundf(player->unit_pos.x + cos(player->viewing_angle - M_PI / 1.5) * GRID_SIZE / 3);
	player_vertices[2].y = roundf(player->unit_pos.y + -sin(player->viewing_angle - M_PI / 1.5) * GRID_SIZE / 3);

	draw_triangle(cub, player_vertices, 0x52dee5, 1);

	for (int i = 0; i < WIN_WIDTH; i++) {
		draw_line(cub, cub->player.unit_pos, cub->rays[i].p_intersection, 0xbffcc6);
	}
}