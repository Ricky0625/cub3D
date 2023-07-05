/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:27:54 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/05 16:18:35 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	cub->doors = NULL;
	init_images(cub);
	init_player(&cub->player);
	init_hand_animation(cub);
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
	cub3d_hooks(&cub);
	return (0);
}
