/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:05:31 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/03 13:46:13 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_cub(t_cub *cub)
{
	exit_cub(cub, NULL);
	return (0);
}

void	change_key_state(int key, t_cub *cub, int state)
{
	if (!cub->render_opt.using_mouse)
	{
		if (key == KEY_UP)
			cub->active_key.up = state;
		else if (key == KEY_DOWN)
			cub->active_key.down = state;
		else if (key == KEY_LEFT)
			cub->active_key.left = state;
		else if (key == KEY_RIGHT)
			cub->active_key.right = state;
	}
	if (key == KEY_W)
		cub->active_key.w = state;
	else if (key == KEY_S)
		cub->active_key.s = state;
	else if (key == KEY_A)
		cub->active_key.a = state;
	else if (key == KEY_D)
		cub->active_key.d = state;
}

int	key_up_hook(int key, t_cub *cub)
{
	change_key_state(key, cub, 0);
	return (0);
}

int	key_down_hook(int key, t_cub *cub)
{
	if (key == KEY_ESC)
		close_cub(cub);
	else if (key == KEY_PLUS || key == KEY_MINUS)
		adjust_fov(cub, key);
	else if (key == KEY_F || key == KEY_TAB || key == KEY_M)
		change_raycasting_option(cub, key);
	else if (key == KEY_LSHIFT)
		toggle_mouse(cub);
	else if (key == KEY_R)
		reset_raycasting_environment(cub);
	else if (key == KEY_E)
		toggle_door(cub);
	else
		change_key_state(key, cub, 1);
	return (0);
}
