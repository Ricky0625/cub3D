/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:25:50 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/23 16:50:02 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub3d_hooks(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, key_hook, cub);
	// mlx_hook(cub->win, 6, 1L << 6, mouse_hook, cub);
	mlx_hook(cub->win, 17, 0L, close_cub, cub);
	mlx_loop(cub->mlx);
}
