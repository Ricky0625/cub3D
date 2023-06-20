/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:59:17 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/17 16:29:42 by wricky-t         ###   ########.fr       */
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
int	check_elements_all_set(t_texture *textures)
{
	return (
		textures->no_tex.ref != NULL
		&& textures->so_tex.ref != NULL
		&& textures->ea_tex.ref != NULL
		&& textures->we_tex.ref != NULL
		&& textures->ceil_set == 1
		&&textures->floor_set == 1
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
int	check_surrounded(t_map *map, int y, int x)
{
	if (y == 0 || x == 0 || y == map->size.y
		|| x == (int)ft_strlen(map->map[y]))
		return (0);
	if (ft_strchr("10NSWE", map->map[y][x + 1]) == NULL)
		return (0);
	if (ft_strchr("10NSWE", map->map[y][x - 1]) == NULL)
		return (0);
	if (ft_strchr("10NSWE", map->map[y + 1][x]) == NULL)
		return (0);
	if (ft_strchr("10NSWE", map->map[y - 1][x]) == NULL)
		return (0);
	return (1);
}
