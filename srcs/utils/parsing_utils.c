/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:53:22 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/11 12:37:09 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief dummy function for llto2darr
 */
void	*llto2darr_func(void *content)
{
	return (content);
}

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