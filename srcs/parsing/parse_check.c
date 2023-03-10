/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:59:17 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/10 15:12:38 by wricky-t         ###   ########.fr       */
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
