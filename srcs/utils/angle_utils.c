/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:21:38 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/20 16:59:20 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180));
}

double	rad_to_deg(double rad)
{
	return (rad * (180 / M_PI));
}
