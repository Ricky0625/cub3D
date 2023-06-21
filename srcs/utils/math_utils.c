/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:12:43 by wxuerui           #+#    #+#             */
/*   Updated: 2023/06/21 19:12:49 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_distance(t_vector p1, t_vector p2)
{
	return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

double	get_gradient(t_vector p1, t_vector p2)
{
	return -((double)(p2.y - p1.y) / (double)(p2.x - p1.x));
}