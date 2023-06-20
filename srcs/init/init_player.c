/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:49 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/20 11:54:07 by wricky-t         ###   ########.fr       */
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
}

/**
 * @brief Set player's initial state when we found a player in the map
*/
void	set_player_initial_state(t_cub *cub, int row, int column)
{
	char		grid;
	t_player	*player;

	grid = cub->map.map[row][column];
	player = &cub->player;
	player->dir = grid;
	player->grid_pos = (t_vector){column, row};
}
