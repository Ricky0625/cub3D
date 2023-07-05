/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_animation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:06:21 by wxuerui           #+#    #+#             */
/*   Updated: 2023/07/05 17:16:19 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	play_animation(t_cub *cub)
{
	int	index;

	index = cub->render_opt.animation_index;
	if (index >= 5 || index == -1)
		mlx_put_image_to_window(cub->mlx, cub->win, cub->hand_animation[0].ref, WIN_WIDTH - 500, WIN_HEIGHT - 480);
	else
	{
		mlx_put_image_to_window(cub->mlx, cub->win, cub->hand_animation[index].ref, WIN_WIDTH - 500, WIN_HEIGHT - 480);
		++cub->render_opt.animation_index;
	}
	if (cub->render_opt.animation_index >= 5)
		cub->render_opt.animation_index = -1;
}