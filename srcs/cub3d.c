/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:27:54 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/07 19:23:05 by wricky-t         ###   ########.fr       */
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
	cub->win = mlx_new_window(cub->mlx, WIN_WDITH, WIN_HEIGHT, "CUB3D");
}

int	main(int ac, char **av)
{
	t_cub	cub;

	(void)av;
	if (ac < 2)
		return (show_error(NULL, NO_MAP));
	else if (ac > 2)
		return (show_error(NULL, TOO_MUCH_MAP));
	init_cub(&cub);
	mlx_loop(cub.mlx);
	return (1);
}
