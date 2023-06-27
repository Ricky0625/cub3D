/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:05:31 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/27 11:38:37 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_cub(t_cub *cub)
{
	exit_cub(cub, NULL);
	return (0);
}

int	key_hook(int key, t_cub *cub)
{
	if (key == KEY_ESC)
		close_cub(cub);
	else if (key == KEY_PLUS || key == KEY_MINUS)
		adjust_fov(cub, key);
	else if (key == KEY_Q || key == KEY_E)
		adjust_center_offset(cub, key);
	else if (key == KEY_F || key == KEY_M)
		change_raycasting_option(cub, key);
	else if (!cub->render_opt.using_mouse
		&& (key == KEY_LEFT || key == KEY_RIGHT))
		rotate_player(cub, key, TURN_SPEED);
	else if (key == KEY_LSHIFT)
		cub->render_opt.using_mouse = !cub->render_opt.using_mouse;
	else if (key == KEY_R)
		reset_raycasting_environment(cub);
	else if (key == KEY_W || key == KEY_S
		|| key == KEY_A || key == KEY_D)
		move_player(cub, key);
	return (0);
}
