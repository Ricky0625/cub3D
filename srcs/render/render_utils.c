/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:42:09 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/03 12:53:01 by wxuerui          ###   ########.fr       */
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
	if (ray->door_info != NULL && get_door_info(cub, ray->p_intersection))
	{
		slice->texture = &cub->textures.door_tex;
		return ;
	}
	if (ray->ray_ortt == HORIZONTAL)
	{
		if (ray->angle > 0 && ray->angle < M_PI)
			slice->texture = &cub->textures.no_tex;
		else
			slice->texture = &cub->textures.so_tex;
	}
	else if (ray->ray_ortt == VERTICAL)
	{
		if (ray->angle > M_PI_2 && ray->angle < M_PI_2 * 3)
			slice->texture = &cub->textures.we_tex;
		else
			slice->texture = &cub->textures.ea_tex;
	}
}

/**
 * @brief Determine the offset of the texture.
 * 
 * @param ray the ray struct (each individual ray)
 * @param slice the slice struct (each individual slice)
 * @param col_index the index of the column (y-axis)
 * 
 * @details
 * Based on the orientation of the ray, calculate the texture offset.
*/
void	get_tex_offset(t_ray *ray, t_slice *slice)
{
	t_img	*tex;
	double	grid_offset;

	tex = slice->texture;
	if (ray->ray_ortt == HORIZONTAL)
	{
		grid_offset = fmod(ray->p_intersection.x, GRID_SIZE);
		if (ray->angle > M_PI)
			grid_offset = GRID_SIZE - grid_offset;
		slice->offset = grid_offset / GRID_SIZE * tex->size.x;
	}
	else if (ray->ray_ortt == VERTICAL)
	{
		grid_offset = fmod(ray->p_intersection.y, GRID_SIZE);
		if (ray->angle > M_PI_2 && ray->angle < M_PI_2 * 3)
			grid_offset = GRID_SIZE - grid_offset;
		slice->offset = grid_offset / GRID_SIZE * tex->size.x;
	}
}
