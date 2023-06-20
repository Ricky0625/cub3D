/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:03:08 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/20 14:47:30 by wxuerui          ###   ########.fr       */
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

	delta.x = abs(p2.x - p1.x);
	delta.y = -abs(p2.y - p1.y);
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

void	draw_circle(t_cub *cub, t_vector center, float r, int color)
{
	float	x = 0;
	float	y = 0;
	
	if (r < 0)
		return ;
	if (center.x + r > WIN_WIDTH || center.x - r < 0
		|| center.y + r > WIN_HEIGHT || center.y - r < 0)
		return ;
	for (int y = center.y - r; y <= center.y + r; y++) {
		x = sqrt(pow(r, 2) - pow(y - center.y, 2)) + center.x;
		draw_line(cub, center, (t_vector){roundf(x), y}, color);
		draw_line(cub, center, (t_vector){2 * center.x - roundf(x), y}, color);
	}
	for (int x = center.x - r; x <= center.x + r; x++) {
		y = sqrt(pow(r, 2) - pow(x - center.x, 2)) + center.y;
		draw_line(cub, center, (t_vector){x, roundf(y)}, color);
		draw_line(cub, center, (t_vector){x, 2 * center.y - roundf(y)}, color);
	}
}