/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_manual.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:48:07 by wxuerui           #+#    #+#             */
/*   Updated: 2023/07/03 14:01:44 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_manual(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx, cub->win, cub->manual.ref, WIN_WIDTH - MANUAL_WIDTH, 0);
}