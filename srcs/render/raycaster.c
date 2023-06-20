/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:38:27 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/20 21:27:34 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Steps to cast a ray (Untextured world)
 * 1. Based on the player's viewing angle, substract FOV / 2. This is the
 * 	  leftmost ray angle.
 * 2. Loop from column to column,
 * 		a. cast a ray
 * 		b. trace the ray until it hits a wall
 * 3. Record the distance to wall (distance is the length of the ray)
 * 4. Add the angle step to the ray angle so it moves to the right
 * 5. Repeat step 2 to step 3 until the all 320 rays are cast
*/

void	find_first_intersection(t_orientation ortt)
{}

/**
 * Steps to check horizontal intersections
 * 1. Find the first intersection
 * 2. From the first intersection, find the next intersection (x + x_step, y + y_step)
 * 3. Repeat step 2 until the intersection is a wall
*/
// t_ray	check_horizontal_intersection(t_cub *cub, double cast_angle)
// {
// 	t_ray		h_ray;
// 	t_vector_d	step_size;

// 	init_step_size(&step_size, cast_angle, HORIZONTAL);
// 	/**
// 	 * while (collision is not wall)
// 	 * {
// 	 * 		// increment step size
// 	 * }
// 	 * // find distance to wall
// 	*/
// 	return (h_ray);
// }

// t_ray	check_vertical_intersection(t_cub *cub, double cast_angle)
// {
// 	t_ray		v_ray;
// 	t_vector_d	step_size;

// 	init_step_size(&step_size, cast_angle, VERTICAL);
// 	/**
// 	 * while (collision is not wall)
// 	 * {
// 	 * 		// increment step size
// 	 * }
// 	 * // find distance to wall
// 	*/
// 	return (v_ray);
// }

t_ray	check_intersection(t_cub *cub, double cast_angle, t_orientation ortt)
{
	t_ray		ray;
	t_vector_d	step_size;

	init_step_size(&step_size, cast_angle, ortt);
	/**
	 * while (collision is not wall)
	 * {
	 * 		// increment step size
	 * }
	 * // find distance to wall
	*/
	return (ray);
}

// do not fix fish eye effect here
// maybe can make this function return a ray struct
void	cast_ray(t_cub *cub, double cast_angle)
{
	t_ray	h_ray;
	t_ray	v_ray;

	h_ray = check_intersection(cub, cast_angle, HORIZONTAL);
	v_ray = check_intersection(cub, cast_angle, VERTICAL);
	if (h_ray.dist <= v_ray.dist)
	{
		printf("h_ray is selected\n");
	}
	else
	{
		printf("v_ray is selected\n");
	}
}

/**
 * Need to do:
 * 1. A loop that casts all rays []
 * 		- iterate through each column
 * 		- increment cast_angle by ray_angle_step each iteration
 * 		- cast ray
 * 2. A function that cast ray []
 * 3. A function that trace ray (inside function 2) []
 * 4. A function that checks horizontal intersection (inside function 3) []
 * 5. A function that checks vertical intersection (inside function 3) []
 * 5. A funciton that picks which intersection is closer (inside function 3) []
*/
void	raycaster(t_cub *cub)
{
	int		col_index;
	double	cast_angle;

	col_index = -1;
	cast_angle = cub->player.viewing_angle - deg_to_rad(FOV / 2);
	while (++col_index < WIN_WIDTH)
	{
		// store the returned ray struct in an array
		// rays[col_index] = cast_ray(cub, col_index);
		cast_angle += cub->proj_attr.ray_angle_step;
	}
	(void)cub;
}
