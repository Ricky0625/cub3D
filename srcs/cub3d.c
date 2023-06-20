/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:27:54 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/20 21:13:50 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test_raycast(t_cub *cub)
{
	t_vector	player_vertices[3];
	t_player	*player = &cub->player;

	// Render the background map
	for (int y = 0; y < (int)(GRID_SIZE * cub->map.size.y); y++) {
		for (int x = 0; x < (int)(GRID_SIZE * ft_strlen(cub->map.map[y / GRID_SIZE])); x++) {
			if (cub->map.map[y / GRID_SIZE][x / GRID_SIZE] == '0' || ft_strchr(PLY_DIR, cub->map.map[y / GRID_SIZE][x / GRID_SIZE]))
				draw_pixel(cub, x, y, 0xf6f6eb);
			else if (cub->map.map[y / GRID_SIZE][x / GRID_SIZE] == '1')
				draw_pixel(cub, x, y, 0xd5d6ea);
			else
				draw_pixel(cub, x, y, 0);
		}
	}

	// Update player
	// draw_circle(cub, cub->player.unit_pos, 5, 0x00ff00);
	player_vertices[0].x = roundf(player->unit_pos.x + cos(player->viewing_angle) * GRID_SIZE / 2);
	player_vertices[0].y = roundf(player->unit_pos.y + -sin(player->viewing_angle) * GRID_SIZE / 2);
	player_vertices[1].x = roundf(player->unit_pos.x + cos(player->viewing_angle + M_PI / 1.5) * GRID_SIZE / 3);
	player_vertices[1].y = roundf(player->unit_pos.y + -sin(player->viewing_angle + M_PI / 1.5) * GRID_SIZE / 3);
	player_vertices[2].x = roundf(player->unit_pos.x + cos(player->viewing_angle - M_PI / 1.5) * GRID_SIZE / 3);
	player_vertices[2].y = roundf(player->unit_pos.y + -sin(player->viewing_angle - M_PI / 1.5) * GRID_SIZE / 3);

	draw_triangle(cub, player_vertices, 0x52dee5, 1);

	// 0xbffcc6 ray
	// draw_line(cub, player->unit_pos, player_vertices[0], 0);



	mlx_put_image_to_window(cub->mlx, cub->win, cub->buffer.ref, 0, 0);
}

/**
 * @brief Initialize main struct
 * 
 * @param cub Pointer to main struct
 * 
 * @details
 * Initialize everything needed for cub3d to work
*/
static void	init_cub(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	cub->map.info_list = NULL;
	init_player(&cub->player);
}


/**
 * @brief cub3d entry point
 * 
 * @var cub Cub3d main struct
 * 
 * @details
 * 1. Check if ac is 2. If not, exit with error
 * 2. Initialize main struct
 * 3. Parse map
*/
int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac < 2)
		exit_cub(NULL, NO_MAP);
	else if (ac > 2)
		exit_cub(NULL, TOO_MANY_MAP);
	init_cub(&cub);
	parse_map(&cub, av[1]);
	new_image(&cub, &cub.buffer, (t_vector){GRID_SIZE * cub.map.size.x, GRID_SIZE * cub.map.size.y});
	test_raycast(&cub);
	cub3d_hooks(&cub);
	return (0);
}
