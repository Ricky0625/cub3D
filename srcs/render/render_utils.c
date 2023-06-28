/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:42:09 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/28 15:56:16 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Determine which texture to use for the wall.
 * 
 * @param cub the main struct
 * @param ray the ray struct (each individual ray)
 * 
 * @return t_img* the texture to use (pointer to the texture struct)
 * 
 * @details
 * This function determines the texture to use for the wall based on the
 * orientation of the ray, and the angle of the ray.
*/
void	get_wall_texture(t_cub *cub, t_ray *ray, t_slice *slice)
{
	slice->texture = &cub->textures.no_tex;
}

void	get_tex_offset(t_ray *ray, t_slice *slice, int col_index)
{
	if (ray->ray_ortt == HORIZONTAL)
	{
		slice->tex_pos.x = col_index * 4;
		slice->tex_pos.y = ((int)ray->p_intersection.y % GRID_SIZE) * slice->texture->line_size;
	}
	else if (ray->ray_ortt == VERTICAL)
	{
		slice->tex_pos.x = ((int)ray->p_intersection.x % slice->texture->size.x) * 4;
		slice->tex_pos.y = col_index * slice->texture->line_size;
	}
}
