/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 19:03:08 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/28 21:50:08 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	if (x < 0 || y < 0)
		return ;
	i = (x * cub->buffer.bpp / 8) + (y * cub->buffer.line_size);
	cub->buffer.data[i] = color;
	cub->buffer.data[++i] = color >> 8;
	cub->buffer.data[++i] = color >> 16;
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

// Each pixel of a texture image is stored inside an array of chars.
// Each pixel is 4 integer, which compromises of 4 value in colors. ARGB.
// Create a function that extract the texture column from the texture image and draw it to the buffer
// It will mainly have two parameters, the cub and the slice.
// Slice basically has everything you need to know to draw the slice on the screen.
// Below are the member of the struct:
// 1. The slice height
// 2. The texture image
// 3. The starting point to copy the texture from (offset)
// 4. The ending point to copy the texture from
// 5. The destination point to copy the texture to
// 6. The texture step size, which is used to skip/repeat a pixel in the texture image

// DISCOVERY: Typecast the texture data to int, then you can access the color of the pixel.
void	draw_slice(t_cub *cub, t_slice *slice)
{
	t_img		*texture;
	int			*texture_data;
	t_vector_d	start;

	(void)cub;
	texture = slice->texture;
	texture_data = (int *)texture->data;
	// printf("width: %d, height: %d\n", texture->size.x, texture->size.y);
	// line size is basically width * 4
	// printf("line size: %d\n", texture->line_size);
	// texture size x is width, y is height
	// start.x is row, start.y is column
	while ((int)start.x < texture->size.y) // wait. isn't it iterate through row enough? since we are drawing a column?
	{
		// start.y = 0;
		// while (start.y < texture->size.x)
		// {
			// printf("color[%d,%d]: %08X ", (int)start.x, (int)start.y, texture_data[(int)start.x * texture->size.x + (int)start.y]);
		// 	start.y++;
		// }
		// printf("\n");
		printf("start.x in double: %f, truncated: %d, color: %08X\n", start.x, (int)start.x, texture_data[(int)start.x * texture->size.x + (int)start.y]);
		start.x += slice->tex_step;
	}
}

/**
 * IDEAS:
 * 
 * 1. Seems like i just need the index of the target column in the texture image. So I get rid of slice->texture_start to just one double value that represents the index of the row.
 * 2. Need to find the ending row, which is the row that I should stop copying the texture from.
 * 3. Need to find the starting row, which is the row that I should start copying the texture from. (when the slice height is greater than the texture height)
*/

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
