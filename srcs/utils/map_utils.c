/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:11:45 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/20 11:45:51 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_iterator(t_cub *cub, t_map_iterator_func f, t_iterate_type type)
{
	int		row;
	int		column;
	t_map	*map;
	char	**map_content;

	row = -1;
	map = &cub->map;
	map_content = map->map;
	while (map_content[++row])
	{
		if (type == ROW)
		{
			f(cub, row, -1);
			continue ;
		}
		column = -1;
		while (map_content[row][++column])
			f(cub, row, column);
	}
}
