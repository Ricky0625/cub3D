/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:40:10 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/14 16:34:50 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_texture *texture)
{
	texture->no_tex.ref = NULL;
	texture->so_tex.ref = NULL;
	texture->we_tex.ref = NULL;
	texture->ea_tex.ref = NULL;
	texture->door_tex.ref = NULL;
	texture->mm_floor.ref = NULL;
	texture->mm_wall.ref = NULL;
	texture->ceil_set = 0;
	texture->floor_set = 0;
}

/**
 * @brief Add door to the doors list
 * 
 * @param cub main structure
 * @param y column index
 * @param x row index
*/
void	add_door(t_cub *cub, int y, int x)
{
	t_door	*door;

	door = malloc(sizeof(t_door));
	if (!door)
		exit_cub(cub, MALLOC_FAIL);
	door->grid_pos = (t_vector){y, x};
	door->state = CLOSED;
	ft_lstadd_back(&cub->doors, ft_lstnew(door));
}
