/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:19:55 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/27 12:02:24 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Render the square background map
 * From start to end, put the corresponding colors.
 * If at '1', draw wall color.
 * else if at ' ', draw void color.
 * else ('0', player), draw floor color;
 * 
 * All x and y are offset by their start to make them at the top left corner.
*/
void	mm_put_background(t_cub *cub, char **map, t_vector start, t_vector end)
{
	int	x;
	int	y;

	y = start.y - 1;
	while (++y < end.y)
	{
		x = start.x - 1;
		while (++x < MM_TILE_SIZE * (int)ft_strlen(map[y / MM_TILE_SIZE])
			&& x < end.x)
		{
			if (map[y / MM_TILE_SIZE][x / MM_TILE_SIZE] == '1')
				draw_pixel(cub, x - start.x, y - start.y, MM_COLOR_WALL);
			else if (map[y / MM_TILE_SIZE][x / MM_TILE_SIZE] == ' ')
				draw_pixel(cub, x - start.x, y - start.y, MM_COLOR_VOID);
			else
				draw_pixel(cub, x - start.x, y - start.y, MM_COLOR_FLOOR);
		}
	}
}

/**
 * Draw the player triangle on the minimap with scale.
 * 
 * Player is a isosceles triangle, not equilateral,
 * that's why some divide by 2 and some by 3.
 * 
 * Hint: M_PI / 1.5 is 120 deg
*/
void	mm_put_player(t_cub *cub, t_vector start, double scale)
{
	t_vector	vertices[3];
	int			x;
	int			y;

	x = cub->player.unit_pos.x * scale - start.x;
	y = cub->player.unit_pos.y * scale - start.y;
	vertices[0].x = roundf(x
			+ cos(cub->player.viewing_angle) * MM_TILE_SIZE / 2);
	vertices[0].y = roundf(y
			+ -sin(cub->player.viewing_angle) * MM_TILE_SIZE / 2);
	vertices[1].x = roundf(x
			+ cos(cub->player.viewing_angle + M_PI / 1.5) * MM_TILE_SIZE / 3);
	vertices[1].y = roundf(y
			+ -sin(cub->player.viewing_angle + M_PI / 1.5) * MM_TILE_SIZE / 3);
	vertices[2].x = roundf(x
			+ cos(cub->player.viewing_angle - M_PI / 1.5) * MM_TILE_SIZE / 3);
	vertices[2].y = roundf(y
			+ -sin(cub->player.viewing_angle - M_PI / 1.5) * MM_TILE_SIZE / 3);
	draw_triangle(cub, vertices, MM_COLOR_PLAYER, 1);
}

/**
 * Scale the player upos and every single ray.
 * Use the dedicated mm_draw_ray function to avoid ray exceeding the minimap.
*/
void	mm_put_rays(t_cub *cub, t_vector start, double scale)
{
	t_vector	scaled_player_upos;
	t_vector	scaled_ray_p_inter;
	int			i;

	scaled_player_upos.x = cub->player.unit_pos.x * scale - start.x;
	scaled_player_upos.y = cub->player.unit_pos.y * scale - start.y;
	i = -1;
	while (++i < WIN_WIDTH)
	{
		scaled_ray_p_inter.x = cub->rays[i].p_intersection.x * scale - start.x;
		scaled_ray_p_inter.y = cub->rays[i].p_intersection.y * scale - start.y;
		mm_draw_ray(cub, scaled_player_upos, scaled_ray_p_inter, MM_COLOR_RAY);
	}
}

/**
 * Start and End are for transforming pixels for later use.
 * The pixels will be all at the top left corner to form a minimap.
 * Offset is for start and end to get their relative position in the minimap.
*/
void	render_minimap(t_cub *cub)
{
	t_vector	start;
	t_vector	end;
	double		scale;
	int			offset;

	scale = cub->proj_attr.mm_scale;
	offset = MM_SIZE / 2 * MM_TILE_SIZE;
	start.x = (int)roundf(cub->player.unit_pos.x * scale) - offset;
	start.y = (int)roundf(cub->player.unit_pos.y * scale) - offset;
	end.x = (int)roundf(cub->player.unit_pos.x * scale) + offset;
	end.y = (int)roundf(cub->player.unit_pos.y * scale) + offset;
	mm_adjust_start_and_end(cub, &start, &end);
	mm_put_background(cub, cub->map.map, start, end);
	mm_put_player(cub, start, cub->proj_attr.mm_scale);
	mm_put_rays(cub, start, cub->proj_attr.mm_scale);
}
