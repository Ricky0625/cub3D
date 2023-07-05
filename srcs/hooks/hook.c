/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:25:50 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/05 18:21:56 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_player_state(t_cub *cub)
{
	if (cub->active_key.w)
		move_player(cub, KEY_W);
	if (cub->active_key.a)
		move_player(cub, KEY_A);
	if (cub->active_key.s)
		move_player(cub, KEY_S);
	if (cub->active_key.d)
		move_player(cub, KEY_D);
	if (cub->active_key.left)
		rotate_player(cub, KEY_LEFT, TURN_SPEED);
	if (cub->active_key.right)
		rotate_player(cub, KEY_RIGHT, TURN_SPEED);
	if (cub->active_key.up)
		adjust_center_offset(cub, KEY_UP, CENTER_OFFSET_STEP);
	if (cub->active_key.down)
		adjust_center_offset(cub, KEY_DOWN, -CENTER_OFFSET_STEP);
	if (cub->render_opt.mouse_rotate_speed)
	{
		if (cub->render_opt.mouse_rotate_speed > 0)
			rotate_player(cub, KEY_RIGHT, cub->render_opt.mouse_rotate_speed);
		else
			rotate_player(cub, KEY_LEFT, -cub->render_opt.mouse_rotate_speed);
		cub->render_opt.mouse_rotate_speed = 0;
	}
}

static int	rendering(t_cub *cub)
{
	update_player_state(cub);
	mlx_clear_window(cub->mlx, cub->win);
	store_rays_to_cub(cub);
	ft_bzero(cub->buffer.data, cub->buffer.size.x * cub->buffer.size.y * 4);
	put_color_to_image(&cub->minimap, MM_COLOR_VOID, MM_IMG_SIZE * MM_IMG_SIZE);
	render_world(cub);
	if (cub->render_opt.minimap)
		render_minimap(cub);
	play_animation(cub);
	if (cub->render_opt.manual)
		put_manual(cub);
	else
		put_manual_string(cub, (t_vector){WIN_WIDTH - 180, WIN_HEIGHT - 30},
			"Press M to Open Manual", 0);
	return (0);
}

/**
 * @brief Listen to mouse click hook
 * 
 * @details
 * Check if it's using mouse to control, if yes, and it's left click, then
 * open door.
 * 
 * @attention button 1 means left click
*/
static int	mouse_click_hook(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (cub->render_opt.using_mouse && button == 1)
	{
		cub->render_opt.animation_index = 0;
		toggle_door(cub);
	}
	return (0);
}

void	cub3d_hooks(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, key_down_hook, cub);
	mlx_hook(cub->win, 3, 1L << 0, key_up_hook, cub);
	mlx_hook(cub->win, 6, 1L << 6, mouse_hook, cub);
	mlx_hook(cub->win, 4, 1L << 2, mouse_click_hook, cub);
	mlx_hook(cub->win, 17, 0L, close_cub, cub);
	mlx_loop_hook(cub->mlx, rendering, cub);
	mlx_loop(cub->mlx);
}
