/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:03:08 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/22 15:23:26 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_cub *cub, int x, int y, int color)
{
	int		i;

	if (x < 0 || y < 0)
		return ;
	i = (x * cub->buffer.bpp / 8) + (y * cub->buffer.line_size);
	cub->buffer.data[i] = color;
	cub->buffer.data[++i] = color >> 8;
	cub->buffer.data[++i] = color >> 16;
}

void	draw_line(t_cub *cub, t_vector p1, t_vector p2, int color)
{
	t_vector	dir;
	t_vector	delta;
	int			error[2];

	delta.x = int_abs(p2.x - p1.x);
	delta.y = -int_abs(p2.y - p1.y);
	dir.x = -1 + (2 * (p2.x >= p1.x));
	dir.y = -1 + (2 * (p2.y >= p1.y));
	error[0] = delta.x + delta.y;
	while (p1.x != p2.x || p1.y != p2.y)
	{
		draw_pixel(cub, p1.x, p1.y, color);
		error[1] = 2 * error[0];
		if (error[1] >= delta.y)
		{
			p1.x += dir.x;
			error[0] += delta.y;
		}
		else if (error[1] <= delta.x)
		{
			p1.y += dir.y;
			error[0] += delta.x;
		}
	}
}

void	fill_triangle(t_cub *cub, t_vector *vects, int color)
{
	t_vector	dir;
	t_vector	delta;
	int			error[2];

	delta.x = int_abs(vects[2].x - vects[1].x);
	delta.y = -int_abs(vects[2].y - vects[1].y);
	dir.x = -1 + (2 * (vects[2].x >= vects[1].x));
	dir.y = -1 + (2 * (vects[2].y >= vects[1].y));
	error[0] = delta.x + delta.y;
	while (vects[1].x != vects[2].x || vects[1].y != vects[2].y)
	{
		draw_line(cub, vects[0], vects[1], color);
		error[1] = 2 * error[0];
		if (error[1] >= delta.y)
		{
			vects[1].x += dir.x;
			error[0] += delta.y;
		}
		else if (error[1] <= delta.x)
		{
			vects[1].y += dir.y;
			error[0] += delta.x;
		}
	}
}

void	draw_triangle(t_cub *cub, t_vector *vects, int color, int fill)
{
	// Draw the sides of the triangle
	draw_line(cub, vects[0], vects[1], color);
	draw_line(cub, vects[0], vects[2], color);
	draw_line(cub, vects[1], vects[2], color);
	if (fill) // if fill is true
		fill_triangle(cub, vects, color);
}