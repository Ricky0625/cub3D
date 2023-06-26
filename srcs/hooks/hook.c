/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:25:50 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/26 18:28:52 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rendering(t_cub *cub)
{
	// new_image(cub, &cub->buffer, (t_vector){WIN_WIDTH, WIN_HEIGHT});
	store_rays_to_cub(cub);
	// render_world(cub);
	// if (cub->render_opt.minimap)
		// render_minimap(cub);
	// mlx_put_image_to_window(cub->mlx, cub->win, cub->buffer.ref, 0, 0);
	// mlx_destroy_image(cub->mlx, cub->buffer.ref);
	return (0);
}

void	cub3d_hooks(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, key_hook, cub);
	mlx_hook(cub->win, 6, 1L << 6, mouse_hook, cub);
	mlx_hook(cub->win, 17, 0L, close_cub, cub);
	mlx_loop_hook(cub->mlx, rendering, cub);
	mlx_loop(cub->mlx);
}
