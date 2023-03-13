/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:07:40 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/13 14:53:55 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Get the color value in integer type
 * @details
 * In little endian machines, the color format will be BGRA. While in big
 * endian machines, the color format will be ARGB. Hence, check if the
 * endian is (0 = small OR 1 = big). If it's small, reverse the array
 * before convert it into integer value.
*/
int	create_rgba(t_cub *cub, unsigned char color[4])
{
	if (cub->buffer.ref != NULL && cub->buffer.endian == 0)
		ft_revarr(color, TOTAL_RGBA, sizeof(unsigned char));
	return (*(int *)color);
}

/**
 * For testing purpose only
*/
void	print_color(t_cub *cub, unsigned char color[4])
{
	int	code;

	code = create_rgba(cub, color);
	printf("code: %X\n", code);
}
