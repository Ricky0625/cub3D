/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:28:38 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/05 14:02:00 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief toggle mouse control
*/
void	toggle_mouse(t_cub *cub)
{
	cub->render_opt.using_mouse = !cub->render_opt.using_mouse;
	if (cub->render_opt.using_mouse)
	{
		change_key_state(KEY_LEFT, cub, 0);
		change_key_state(KEY_RIGHT, cub, 0);
		change_key_state(KEY_UP, cub, 0);
		change_key_state(KEY_DOWN, cub, 0);
		mlx_mouse_hide();
	}
	else
		mlx_mouse_show();
}

/**
 * @brief listen to mouse move event
*/
int	mouse_hook(int x, int y, t_cub *cub)
{
	double	rtt_speed;

	rtt_speed = cub->render_opt.mouse_rotate_speed;
	if (cub->render_opt.using_mouse)
	{
		if (x > WIN_WIDTH / 2)
		{
			rtt_speed = sqrt((x - WIN_WIDTH / 2) / (M_PI_2 / TURN_SPEED)) / 10;
			cub->render_opt.mouse_rotate_speed = rtt_speed;
		}
		else if (x < WIN_WIDTH / 2)
		{
			rtt_speed = -sqrt((WIN_WIDTH / 2 - x) / (M_PI_2 / TURN_SPEED)) / 10;
			cub->render_opt.mouse_rotate_speed = rtt_speed;
		}
		if (y > WIN_HEIGHT / 2)
			adjust_center_offset(cub, KEY_DOWN, WIN_HEIGHT / 2 - y);
		else if (y < WIN_HEIGHT / 2)
			adjust_center_offset(cub, KEY_UP, WIN_HEIGHT / 2 - y);
		mlx_mouse_move(cub->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
	return (0);
}
