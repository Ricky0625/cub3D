/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:27:54 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/23 15:51:20 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rendering(t_cub *cub)
{
	new_image(cub, &cub->buffer, (t_vector){WIN_WIDTH, WIN_HEIGHT});
	store_rays_to_cub(cub);
	if (cub->render_opt.minimap)
		render_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->buffer.ref, 0, 0);
	mlx_destroy_image(cub->mlx, cub->buffer.ref);
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
	cub->map.info_list = NULL;
	init_player(&cub->player);
	init_projection_attribute(&cub->proj_attr);
	init_render_option(&cub->render_opt);
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
	parse_map(&cub, av[1]);
	mlx_loop_hook(cub.mlx, rendering, &cub);
	cub3d_hooks(&cub);
	return (0);
}

/**
 * Projection attributes
 * 
 * 1. Player [DONE]
 * 		- height (assume it's wall height / 2) [DONE]
 * 		- FOV (assume it's 60 degree first) [DONE]
 * 		- position [DONE]
 * 2. Projection plane's dimension []
 * 		* this is basically the window size
 * 3. Relationship between player and projection plane []
*/
