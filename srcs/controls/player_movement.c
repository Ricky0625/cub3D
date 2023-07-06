/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:29:48 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/05 18:21:31 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Move separately on x and y axis
 * and move only when it doesn't run into a wall after move.
*/
static void	move(t_cub *cub, t_vector_d displacement)
{
	t_vector	temp_pos;

	temp_pos.x = cub->player.unit_pos.x + roundf(displacement.x);
	temp_pos.y = cub->player.unit_pos.y;
	if (!collide(cub, temp_pos))
		cub->player.unit_pos.x += roundf(displacement.x);
	temp_pos.x = cub->player.unit_pos.x;
	temp_pos.y = cub->player.unit_pos.y + roundf(displacement.y);
	if (!collide(cub, temp_pos))
		cub->player.unit_pos.y += roundf(displacement.y);
	cub->player.grid_pos.x = cub->player.unit_pos.x / GRID_SIZE;
	cub->player.grid_pos.y = cub->player.unit_pos.y / GRID_SIZE;
}

/**
 * @brief Move player on x axis
*/
static void	move_x(t_cub *cub, t_controls key)
{
	t_vector_d	displacement;

	if (key == KEY_A)
	{
		displacement.x = cub->player.displacement.x * cos(M_PI_2)
			+ cub->player.displacement.y * sin(M_PI_2);
		displacement.y = cub->player.displacement.x * -sin(M_PI_2)
			+ cub->player.displacement.y * cos(M_PI_2);
		move(cub, displacement);
	}
	else if (key == KEY_D)
	{
		displacement.x = cub->player.displacement.x * cos(-M_PI_2)
			+ cub->player.displacement.y * sin(-M_PI_2);
		displacement.y = cub->player.displacement.x * -sin(-M_PI_2)
			+ cub->player.displacement.y * cos(-M_PI_2);
		move(cub, displacement);
	}
}

/**
 * @brief Move player on y axis
*/
static void	move_y(t_cub *cub, t_controls key)
{
	t_vector_d	displacement;

	if (key == KEY_W)
	{
		displacement = cub->player.displacement;
		move(cub, displacement);
	}
	else if (key == KEY_S)
	{
		displacement.x = -cub->player.displacement.x;
		displacement.y = -cub->player.displacement.y;
		move(cub, displacement);
	}
}

/**
 * Horizontal motion controls:
 * 
 * W - move forward
 * S - move backward
 * A - move leftward
 * D - move rightward
 * <- - turn left
 * -> - turn right
 * Mouse move to rotate (like A and D)
*/

/**
 * @brief Move player based on the key
 * 
 * @attention
 * KEY_A and KEY_D - move on x axis
 * KEY_W and KEY_S - move on y axis
*/
void	move_player(t_cub *cub, t_controls key)
{
	if (key == KEY_A || key == KEY_D)
		move_x(cub, key);
	else if (key == KEY_W || key == KEY_S)
		move_y(cub, key);
}

/**
 * @brief Rotate player based on the key
*/
void	rotate_player(t_cub *cub, t_controls key, double angle)
{
	double	new_angle;

	new_angle = cub->player.viewing_angle;
	if (key == KEY_LEFT)
		new_angle += angle;
	else if (key == KEY_RIGHT)
		new_angle -= angle;
	if (new_angle < 0)
		new_angle += 2 * M_PI;
	else if (new_angle >= 2 * M_PI)
		new_angle -= 2 * M_PI;
	cub->player.displacement.x = cos(new_angle) * MOVE_SPEED;
	cub->player.displacement.y = -sin(new_angle) * MOVE_SPEED;
	cub->player.viewing_angle = new_angle;
	update_door_fov(cub);
}
