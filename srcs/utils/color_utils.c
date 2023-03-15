/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:07:40 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/15 19:11:58 by wricky-t         ###   ########.fr       */
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
int	create_argb(t_cub *cub, u_char color[4])
{
	if (cub->buffer.ref != NULL && cub->buffer.endian == 0)
		ft_revarr(color, TOTAL_RGBA, sizeof(unsigned char));
	return (*(int *)color);
}

/**
 * @brief Get the Alpha value out from the color code
 * @details
 * Little endian = BGRA. A at index 3
 * Big endian = ARGB. A at index 0
*/
u_char	get_a(int argb, int endian)
{
	if (endian == 0)
		return (((unsigned char *)&argb)[3]);
	return (((unsigned char *)&argb)[0]);
}

/**
 * @brief Get the Alpha value out from the color code
 * @details
 * Little endian = BGRA. R at index 2
 * Big endian = ARGB. R at index 1
*/
u_char	get_r(int argb, int endian)
{
	if (endian == 0)
		return (((unsigned char *)&argb)[2]);
	return (((unsigned char *)&argb)[1]);
}

/**
 * @brief Get the Alpha value out from the color code
 * @details
 * Little endian = BGRA. R at index 1
 * Big endian = ARGB. R at index 2
*/
u_char	get_g(int argb, int endian)
{
	if (endian == 0)
		return (((unsigned char *)&argb)[1]);
	return (((unsigned char *)&argb)[2]);
}

/**
 * @brief Get the Alpha value out from the color code
 * @details
 * Little endian = BGRA. B at index 0
 * Big endian = ARGB. B at index 3
*/
u_char	get_b(int argb, int endian)
{
	if (endian == 0)
		return (((unsigned char *)&argb)[0]);
	return (((unsigned char *)&argb)[3]);
}
