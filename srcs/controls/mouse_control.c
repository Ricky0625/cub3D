/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:28:38 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/24 16:19:51 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggle_mouse(t_cub *cub)
{
	cub->render_opt.using_mouse = !cub->render_opt.using_mouse;
	if (cub->render_opt.using_mouse)
		mlx_mouse_show();
	else
		mlx_mouse_hide();
}

int	mouse_hook(int x, int y, t_cub *cub)
{
	(void)y;
	if (cub->render_opt.using_mouse)
	{
		if (x > WIN_WIDTH / 2)
			rotate_player(cub, KEY_RIGHT);
		else if (x < WIN_WIDTH / 2)
			rotate_player(cub, KEY_LEFT);
		mlx_mouse_move(cub->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
	return (0);
}
