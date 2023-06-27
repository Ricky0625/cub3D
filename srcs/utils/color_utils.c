/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:07:40 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/24 17:28:41 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Get the color value in integer type
*/
int	create_argb(u_char color[4])
{
	return (color[0] << 24 | color[1] << 16 | color[2] << 8 | color[3]);
}

/**
 * @brief Get the Alpha value out from the color code
*/
u_char	get_a(int argb)
{
	return (((unsigned char *)&argb)[3]);
}

/**
 * @brief Get the Red value out from the color code
*/
u_char	get_r(int argb)
{
	return (((unsigned char *)&argb)[2]);
}

/**
 * @brief Get the Green value out from the color code
*/
u_char	get_g(int argb)
{
	return (((unsigned char *)&argb)[1]);
}

/**
 * @brief Get the Blue value out from the color code
*/
u_char	get_b(int argb)
{
	return (((unsigned char *)&argb)[0]);
}
