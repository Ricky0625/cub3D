/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:03:08 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/29 17:46:41 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line(t_cub *cub, t_vector start, int len, int color)
{
	int	i;

	i = 0;
	while (i < len)
	{
		draw_pixel(cub, start.x, start.y + i, color);
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
void	draw_pixel(t_cub *cub, int x, int y, int color)
{
	int		i;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	i = (x * cub->buffer.bpp / 8) + (y * cub->buffer.line_size);
	cub->buffer.data[i] = get_b(color);
	cub->buffer.data[++i] = get_g(color);
	cub->buffer.data[++i] = get_r(color);
	cub->buffer.data[++i] = get_a(color);
}

/**
 * Draw a line on the screen using the Brehensam's algorithm.
 * Which only uses simple addition and subtraction,
 * instead of expensive calculations such as multiplication and division.
*/
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
		brehensam_algo(&p1, delta, dir, error);
	}
}

void	draw_slice(t_cub *cub, t_slice *slice, int col_index)
{
	t_img		*texture;
	int			*texture_data;
	int			pixel;
	double		texture_start;

	texture = slice->texture;
	texture_data = (int *)texture->data;
	texture_start = 0;
	if (slice->des_start_y < 0)
	{
		texture_start = -slice->des_start_y * slice->tex_step;
		slice->des_start_y = 0;
	}
	while (slice->des_start_y < slice->des_end_y && slice->des_start_y < WIN_HEIGHT)
	{
		if (slice->des_start_y >= 0 && slice->des_start_y < WIN_HEIGHT)
		{
			pixel = texture_data[(int)texture_start * (texture->line_size / 4) + slice->offset];
			draw_pixel(cub, col_index, slice->des_start_y, pixel);
		}
		slice->des_start_y++;
		texture_start += slice->tex_step;
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
void	draw_triangle(t_cub *cub, t_vector *vects, int color, int fill)
{
	t_vector	dir;
	t_vector	delta;
	int			error[2];

	draw_line(cub, vects[0], vects[1], color);
	draw_line(cub, vects[0], vects[2], color);
	draw_line(cub, vects[1], vects[2], color);
	if (fill)
	{
		delta.x = int_abs(vects[2].x - vects[1].x);
		delta.y = -int_abs(vects[2].y - vects[1].y);
		dir.x = -1 + (2 * (vects[2].x >= vects[1].x));
		dir.y = -1 + (2 * (vects[2].y >= vects[1].y));
		error[0] = delta.x + delta.y;
		while (vects[1].x != vects[2].x || vects[1].y != vects[2].y)
		{
			draw_line(cub, vects[0], vects[1], color);
			brehensam_algo(&(vects[1]), delta, dir, error);
		}
	}
}
