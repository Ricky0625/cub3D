/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:49 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/05 17:06:39 by wxuerui          ###   ########.fr       */
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

/**
 * @brief Initialize hand animation frames
*/
void	init_hand_animation(t_cub *cub)
{
	xpm_to_image(cub, &cub->hand_animation[0],
		"assets/hand_animation/frame_0.xpm");
	xpm_to_image(cub, &cub->hand_animation[1],
		"assets/hand_animation/frame_1.xpm");
	xpm_to_image(cub, &cub->hand_animation[2],
		"assets/hand_animation/frame_2.xpm");
	xpm_to_image(cub, &cub->hand_animation[3],
		"assets/hand_animation/frame_3.xpm");
	xpm_to_image(cub, &cub->hand_animation[4],
		"assets/hand_animation/frame_4.xpm");
}

/**
 * @brief Initialize player's viewing angle and displacement
*/
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
 * @brief Update door fov.
 * 
 * @details
 * Door fov is the angle range that use player's viewing angle as center,
 * and minus/plus half of the door fov. If the door is in the fov,
 * meaning that the user can open the door.
 * 
 * @attention
 * door_fov.x is the left side of the fov
 * door_fov.y is the right side of the fov
*/
void	update_door_fov(t_cub *cub)
{
	double				viewing_angle;
	t_projection_attr	*proj_attr;

	viewing_angle = cub->player.viewing_angle;
	proj_attr = &cub->proj_attr;
	proj_attr->door_fov = (t_vector_d){
		viewing_angle - deg_to_rad(DOOR_FOV / 2),
		viewing_angle + deg_to_rad(DOOR_FOV / 2)
	};
}

/**
 * @brief Set player's initial state when we found a player in the map
*/
void	set_player_initial_state(t_cub *cub, int row, int column)
{
	char		grid;
	t_player	*player;
	t_vector_d	unit_pos;

	grid = cub->map.map[row][column];
	player = &cub->player;
	player->dir = grid;
	player->grid_pos = (t_vector){column, row};
	unit_pos.x = column * GRID_SIZE + GRID_SIZE / 2;
	unit_pos.y = row * GRID_SIZE + GRID_SIZE / 2;
	player->unit_pos = unit_pos;
	set_player_viewing_angle(cub);
	update_door_fov(cub);
}
