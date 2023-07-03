/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:59:17 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/20 11:57:23 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the target row is map content or not.
 * 
 * @param str Target row
 * 
 * @return 1 if map content, 0 if not
*/
int	is_map_content(char *str)
{
	if (*str == '\0')
		return (0);
	while (*str != '\0')
	{
		if (ft_strchr(MAP_CHARS, *str++) == NULL)
			return (0);
	}
	return (1);
}

/**
 * @brief Check if all the elements are all set
 * 
 * @param textures texture struct
 * 
 * @return 1 if all set, 0 if not
*/
// shouldn't check if a door texture is set here, since it's optional
int	check_elements_all_set(t_texture *textures)
{
	return (
		textures->no_tex.ref != NULL
		&& textures->so_tex.ref != NULL
		&& textures->ea_tex.ref != NULL
		&& textures->we_tex.ref != NULL
		&& textures->ceil_set == 1
		&& textures->floor_set == 1
	);
}

/**
 * @brief dummy function for llto2darr
 */
void	*llto2darr_func(void *content)
{
	return (content);
}

/**
 * @brief Check if floor tile and player is surrounded by walls
 * 
 * @param map map struct
 * @param y   y coordinate
 * @param x   x coordinate
 * @return 1 if surrounded, 0 if not
 */
static int	check_surrounded(t_cub *cub, int y, int x)
{
	t_map	*map;

	map = &cub->map;
	if (y == 0 || x == 0 || y == map->size.y - 1
		|| x == (int)ft_strlen(map->map[y]) - 1)
		return (0);
	if (ft_strchr("10NSWED", map->map[y][x + 1]) == NULL)
		return (0);
	if (ft_strchr("10NSWED", map->map[y][x - 1]) == NULL)
		return (0);
	if (ft_strchr("10NSWED", map->map[y + 1][x]) == NULL)
		return (0);
	if (ft_strchr("10NSWED", map->map[y - 1][x]) == NULL)
		return (0);
	if (map->map[y][x] == DOOR)
		add_door(cub, y, x);
	return (1);
}

/**
 * @brief helper function for validate map (passing to map_iterator)
 * 
 * @param cub	 main struct
 * @param row	 row index
 * @param column column index
 * 
 * @details
 * 1. If the grid is a player, set the player's initial state
 * 2. If the grid is a floor or a player, check if it is surrounded by walls
*/
void	validate_map(t_cub *cub, int row, int column)
{
	t_map	*map;
	char	grid;

	map = &cub->map;
	grid = map->map[row][column];
	if (ft_strchr(PLY_DIR, grid) != NULL)
	{
		if (cub->player.dir != UNDEFINED)
			exit_cub(cub, TOO_MANY_PLAYERS);
		set_player_initial_state(cub, row, column);
	}
	if (grid == DOOR && cub->textures.door_tex.ref == NULL)
		exit_cub(cub, NO_DOOR_TEXTURE);
	if ((grid == FLOOR || ft_strchr(PLY_DIR, grid) != NULL || grid == DOOR)
		&& check_surrounded(cub, row, column) == 0)
		exit_cub(cub, NOT_SURROUNDED_BY_WALL);
}
