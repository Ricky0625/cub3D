/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:19:55 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/15 15:36:34 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minimap_texture(t_cub *cub)
{
	new_rect(cub, &cub->minimap, (t_vector){MM_WIDTH, MM_HEIGHT}, MM_VOID);
	new_rect(cub, &cub->textures.mm_floor,
		(t_vector){MM_SPT_SIZE, MM_SPT_SIZE}, MM_FLOOR);
	new_rect(cub, &cub->textures.mm_wall,
		(t_vector){MM_SPT_SIZE, MM_SPT_SIZE}, MM_WALL);
	xpm_to_image(cub, &cub->textures.mm_player, "assets/PLAYER.xpm");
}

void	draw_minimap(t_cub *cub)
{
	int			row;
	int			col;
	char		tile;
	t_vector	pos;

	row = -1;
	while (cub->map.map[++row] != NULL)
	{
		col = -1;
		while (cub->map.map[row][++col] != '\0')
		{
			tile = cub->map.map[row][col];
			pos = (t_vector){col * MM_SPT_SIZE, row * MM_SPT_SIZE};
			if (tile == '1')
				copy_image(&cub->textures.mm_wall, &cub->minimap, pos);
			else if (tile == '0' || ft_strchr("NSWE", tile) != NULL)
				copy_image(&cub->textures.mm_floor, &cub->minimap, pos);
		}
	}
}

/**
 * @brief Render out the minimap
 * @details
 * 1. Initialize the textures used by the minimap
 * 2. Iterate through the map and draw out the minimap.
 * 		i. Locate the player, calculate how to place it at the center of the
 *         minimap.
 * 	   ii. Get the start coord and end coord to draw.
 *    iii. Start drawing from start coord to end coord.
 *     iv. Depending on the detected tile type, draw different image.
 * 
 * When initialized, the minimap will have a background color first. Floor
 * and wall will use other color/image.
*/
void	render_minimap(t_cub *cub)
{
	init_minimap_texture(cub);
	draw_minimap(cub);
}
