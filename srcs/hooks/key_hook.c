/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wangxuerui2003@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:05:31 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/23 11:42:56 by wxuerui          ###   ########.fr       */
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
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		rotate_player(cub, key);
	else if (key == KEY_W || key == KEY_S
		|| key == KEY_A || key == KEY_D)
		move_player(cub, key);
	return (0);
}
