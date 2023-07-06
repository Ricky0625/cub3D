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

/**
 * @brief Initialize textures struct
 * 
 * @details
 * By default, all texture references are set to NULL. So to check if a
 * texture is properly initialized, check if the reference is NULL.
*/
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

/**
 * @brief Get the door info struct
 * 
 * @param cub main structure
 * @param ray ray struct (invididual ray)
 * 
 * @details
 * Iterate through the doors list, find one that matches
 * the grid position. If not found, return a NULL pointer.
*/
t_door	*get_door_info(t_cub *cub, t_vector_d p_intersection)
{
	char		**map;
	t_list		*doors;
	t_door		*door_info;
	t_vector	p_grid_pos;

	map = cub->map.map;
	doors = cub->doors;
	p_grid_pos = (t_vector){
		(int)p_intersection.x / GRID_SIZE,
		(int)p_intersection.y / GRID_SIZE
	};
	if (map[p_grid_pos.y][p_grid_pos.x] != DOOR)
		return (NULL);
	while (doors != NULL)
	{
		door_info = (t_door *)doors->content;
		if (door_info->grid_pos.x == p_grid_pos.y
			&& door_info->grid_pos.y == p_grid_pos.x)
			return (door_info);
		doors = doors->next;
	}
	return (NULL);
}

/**
 * @brief Get the door state based on the given grid position
 * 
 * @param cub main structure
 * @param p_grid_pos grid position
 * 
 * @details
 * Return the state of the door when found,
 * otherwise return UNKWOWN_DOOR_STATE.
 * 
 * @attention The vector p_grid_pos should be divided with the GRID_SIZE.
 * If it's for the minimap, divide it with the MM_TILE_SIZE.
*/
int	get_door_state(t_cub *cub, t_vector p_grid_pos)
{
	t_list		*doors;
	t_door		*door_info;

	doors = cub->doors;
	while (doors != NULL)
	{
		door_info = (t_door *)doors->content;
		if (door_info->grid_pos.x == p_grid_pos.y
			&& door_info->grid_pos.y == p_grid_pos.x)
			return (door_info->state);
		doors = doors->next;
	}
	return (UNKWOWN_DOOR_STATE);
}
