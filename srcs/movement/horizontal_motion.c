/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_motion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:29:48 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/22 14:40:18 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Horizontal motion controls:
 * 
 * W - move forward
 * S - move backward
 * A - turn left
 * D - turn right
 * Mouse move to rotate (like A and D)
*/

void	move_player(t_cub *cub, t_controls key)
{	
	if (key == KEY_W)
	{
		cub->player.unit_pos.x += cub->player.displacement.x;
		cub->player.unit_pos.y += cub->player.displacement.y;
	}
	else if (key == KEY_S)
	{
		cub->player.unit_pos.x -= cub->player.displacement.x;
		cub->player.unit_pos.y -= cub->player.displacement.y;
	}
	else if (key == KEY_A)
	{
		cub->player.unit_pos.x += cub->player.displacement.x * cos(M_PI_2) + cub->player.displacement.y * sin(M_PI_2);
		cub->player.unit_pos.y += cub->player.displacement.x * -sin(M_PI_2) + cub->player.displacement.y * cos(M_PI_2);
	}
	else if (key == KEY_D)
	{
		cub->player.unit_pos.x += cub->player.displacement.x * cos(-M_PI_2) + cub->player.displacement.y * sin(-M_PI_2);
		cub->player.unit_pos.y += cub->player.displacement.x * -sin(-M_PI_2) + cub->player.displacement.y * cos(-M_PI_2);
	}
	// printf("%d\n", cub->player.unit_pos.x);
	// printf("%d\n\n", cub->player.unit_pos.y);
}

/**
 * XDisplacement and YDisplacement should be calculated when angle changed
*/
void	rotate_player(t_cub *cub, t_controls key)
{
	double	new_angle;

	new_angle = cub->player.viewing_angle;
	if (key == KEY_LEFT)
		new_angle += TURN_SPEED;
	else if (key == KEY_RIGHT)
		new_angle -= TURN_SPEED;
	if (new_angle < 0)
		new_angle += 2 * M_PI;
	else if (new_angle >= 2 * M_PI)
		new_angle -= 2 * M_PI;
	cub->player.displacement.x = cos(new_angle) * MOVE_SPEED;
	cub->player.displacement.y = -sin(new_angle) * MOVE_SPEED;
	// printf("%f\n", new_angle);
	cub->player.viewing_angle = new_angle;
}
