/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:27:54 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/19 18:19:13 by wangxuerui       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Flow
 * 1. Initialize cub3d
 * 2. Parse map
 * 3. Initialize images
 * 4. Draw
 */

static void	init_cub(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	cub->map.info_list = NULL;
	new_image(cub, &cub->buffer, (t_vector){WIN_WIDTH, WIN_HEIGHT});
	init_textures(&cub->textures);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac < 2)
		exit_cub(NULL, NO_MAP);
	else if (ac > 2)
		exit_cub(NULL, TOO_MANY_MAP);
	init_cub(&cub);
	parse_map(&cub, av[1]);
	render_minimap(&cub);
	mlx_put_image_to_window(cub.mlx, cub.win, cub.minimap.ref, 0, 0);
	mlx_hook(cub.win, 2, 1L << 0, key_hook, &cub);
	mlx_hook(cub.win, 187, 0L, close_cub, &cub);
	mlx_hook(cub.win, DESTROY, LEAVEWINDOW_MASK, close_cub, &cub);
	mlx_loop(cub.mlx);
	return (1);
}
