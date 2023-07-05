/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:03:08 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/05 17:58:19 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line(t_cub *cub, t_vector start, int len, int color)
{
	int	i;

	i = 0;
	while (i < len)
	{
		draw_pixel(&cub->buffer, start.x, start.y + i, color);
		i++;
	}
}

/**
 * The algorithm that determines whether should move on x or y direction.
*/
void	brehensam_algo(t_vector *p, t_vector delta, t_vector dir, int *error)
{
	error[1] = 2 * error[0];
	if (error[1] >= delta.y)
	{
		p->x += dir.x;
		error[0] += delta.y;
	}
	else if (error[1] <= delta.x)
	{
		p->y += dir.y;
		error[0] += delta.x;
	}
}

/**
 * Draw a pixel with color specified at (x, y).
*/
void	draw_pixel(t_img *img, int x, int y, int color)
{
	int		i;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	i = (x * img->bpp / 8) + (y * img->line_size);
	img->data[i] = get_b(color);
	img->data[++i] = get_g(color);
	img->data[++i] = get_r(color);
	img->data[++i] = get_a(color);
}

/**
 * Draw a line on the screen using the Brehensam's algorithm.
 * Which only uses simple addition and subtraction,
 * instead of expensive calculations such as multiplication and division.
*/
void	draw_line(t_img *img, t_vector p1, t_vector p2, int color)
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
		draw_pixel(img, p1.x, p1.y, color);
		brehensam_algo(&p1, delta, dir, error);
	}
}

/**
 * Draw a triangle with color specified.
 * First draw 3 sides, then fill it if param fill is true.
 * 
 * Filling:
 * With vertices A, B and C, draw line from A to B.
 * While B gradually transform to C using the brehensam algo, draw lines too.
 * Kind of like how integration calculates area under curve btw.
*/
void	draw_triangle(t_img *img, t_vector *vects, int color, int fill)
{
	t_vector	dir;
	t_vector	delta;
	int			error[2];

	draw_line(img, vects[0], vects[1], color);
	draw_line(img, vects[0], vects[2], color);
	draw_line(img, vects[1], vects[2], color);
	if (fill)
	{
		delta.x = int_abs(vects[2].x - vects[1].x);
		delta.y = -int_abs(vects[2].y - vects[1].y);
		dir.x = -1 + (2 * (vects[2].x >= vects[1].x));
		dir.y = -1 + (2 * (vects[2].y >= vects[1].y));
		error[0] = delta.x + delta.y;
		while (vects[1].x != vects[2].x || vects[1].y != vects[2].y)
		{
			draw_line(img, vects[0], vects[1], color);
			brehensam_algo(&(vects[1]), delta, dir, error);
		}
	}
}
