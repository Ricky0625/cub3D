/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:05:31 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/21 14:08:02 by wxuerui          ###   ########.fr       */
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
	else if (key == KEY_LEFT || key == KEY_RIGHT
		|| key == KEY_A || key == KEY_D)
		rotate_player(cub, key);
	else if (key == KEY_W || key == KEY_S)
		move_player(cub, key);
	test_raycast(cub);
	return (0);
}
