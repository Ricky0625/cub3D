/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:59:17 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/11 12:54:53 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the target row is map content or not.
*/
int	is_map_content(char *str)
{
	if (*str == '\0')
		return (0);
	while (*str != '\0')
	{
		if (ft_strchr("10NSWE ", *str++) == NULL)
			return (0);
	}
	return (1);
}

/**
 * @brief Check if all the elements are all set
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
 * @brief Check if 0s and player is surrounded by walls
 * 
 * @param map 
 * @param y 
 * @param x 
 * @return int 
 */
int	check_surrounded(t_map *map, int y, int x)
{
	if (y == 0 || x == 0
		|| y == map->size.y
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
