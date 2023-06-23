/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:49 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/23 14:48:40 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Coordinate system used in our cub3d:
 *            
 * 		   -y-axis
 *            ↑
 *  -x-axis ← + → +x-axis
 * 			  ↓
 * 	       +y-axis
 * 
 * 		     90°
 *            ↑
 *     180° ← + → 0°
 * 			  ↓
 * 	       	 270°
*/

/**
 * @brief Initialize player struct
 * 
 * @param player Pointer to player struct
 * 
 * @details
 * Set player direction to UNDEFINED and grid position to (-1, -1)
 */
void	init_player(t_player *player)
{
	player->dir = UNDEFINED;
	player->grid_pos = (t_vector){-1, -1};
	player->viewing_angle = 0.0;
}

static void	set_player_viewing_angle(t_cub *cub)
{
	t_dir	player_facing_direction;

	player_facing_direction = cub->player.dir;
	if (player_facing_direction == NORTH)
		cub->player.viewing_angle = M_PI_2;
	else if (player_facing_direction == SOUTH)
		cub->player.viewing_angle = 3 * M_PI_2;
	else if (player_facing_direction == EAST)
		cub->player.viewing_angle = 0;
	else if (player_facing_direction == WEST)
		cub->player.viewing_angle = M_PI;
	cub->player.displacement.x = cos(cub->player.viewing_angle) * MOVE_SPEED;
	cub->player.displacement.y = -sin(cub->player.viewing_angle) * MOVE_SPEED;
}

/**
 * @brief Set player's initial state when we found a player in the map
*/
void	set_player_initial_state(t_cub *cub, int row, int column)
{
	char		grid;
	t_player	*player;
	t_vector	unit_pos;

	grid = cub->map.map[row][column];
	player = &cub->player;
	player->dir = grid;
	player->grid_pos = (t_vector){column, row};
	unit_pos.x = column * GRID_SIZE + GRID_SIZE / 2;
	unit_pos.y = row * GRID_SIZE + GRID_SIZE / 2;
	player->unit_pos = unit_pos;
	set_player_viewing_angle(cub);
}
