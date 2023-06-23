/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wangxuerui2003@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:27:54 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/23 12:52:37 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rendering(t_cub *cub)
{
	store_rays_to_cub(cub);

	// For Ricky: 3D rendering
	render_minimap(cub);

	mlx_put_image_to_window(cub->mlx, cub->win, cub->buffer.ref, 0, 0);
	return (0);
}

/**
 * @brief Initialize main struct
 * 
 * @param cub Pointer to main struct
 * 
 * @details
 * Initialize everything needed for cub3d to work
*/
static void	init_cub(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	new_image(cub, &cub->buffer, (t_vector){WIN_WIDTH, WIN_HEIGHT});
	cub->map.info_list = NULL;
	init_player(&cub->player);
}

/**
 * @brief cub3d entry point
 * 
 * @var cub Cub3d main struct
 * 
 * @details
 * 1. Check if ac is 2. If not, exit with error
 * 2. Initialize main struct
 * 3. Parse map
*/
int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac < 2)
		exit_cub(NULL, NO_MAP);
	else if (ac > 2)
		exit_cub(NULL, TOO_MANY_MAP);
	init_cub(&cub);
	printf("%f\n", tan(M_PI * 11 / 6));
	parse_map(&cub, av[1]);
	printf("sizex: %d, sizey: %d\n", cub.map.size.x, cub.map.size.y);
	mlx_loop_hook(cub.mlx, rendering, &cub);
	// test_raycast(&cub);
	// render_minimap(&cub);
	cub3d_hooks(&cub);
	return (0);
}
