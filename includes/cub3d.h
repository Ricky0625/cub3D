/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:32:46 by wricky-t          #+#    #+#             */
/*   Updated: 2023/03/07 19:24:06 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ====== LIBRARIES ====== */
# include "../mlx/mlx.h"
# include "lib42.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

/* ====== TEXT STYLING ====== */
# define RED "\033[1;31m"
# define GRN "\033[1;32m"
# define YLW "\033[1;33m"
# define BLU "\033[1;34m"
# define PUR "\033[1;35m"
# define CYN "\033[1;36m"
# define WHT "\033[1;37m"
# define DEF "\033[0m"

/* ====== MACROS ====== */
# define FILE_EXT ".cub"
# define WIN_WDITH 1280
# define WIN_HEIGHT 768
# define SPT_SIZE 128

/* ====== ENUMS ====== */

/**
 * @brief Enum for control key's keycodes.
 * @attention It's for macos only.
*/
typedef enum e_controls
{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_ESC = 53,
	KEY_LEFT = 123,
	KEY_RIGHT = 124
}	t_controls;

/**
 * @brief Enum for error types
*/
typedef enum e_error
{
	NO_MAP,
	TOO_MUCH_MAP
}	t_error;

/* ====== STRUCTS ====== */

/**
 * @brief Vector (x, y)
*/
typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

/**
 * @brief Image and its metadata
*/
typedef struct s_img
{
	void		*ref;
	t_vector	size;
	char		*data;
	int			bpp;
	int			line_size;
	int			endian;
}	t_img;

/**
 * @brief Image caches. Store all the pointers to the textures.
*/
typedef struct s_img_caches
{
	t_img	no_tex;
	t_img	so_tex;
	t_img	we_tex;
	t_img	ea_tex;
}	t_img_caches;

/**
 * @brief The main struct for Cub3D.
*/
typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_img			buffer;
	t_img_caches	caches;
}	t_cub;

/* ====== FUNCTION PROTOTYPES ====== */

// Utils
int		show_error(t_cub *cub, t_error err);

// Img utils
void	new_image(t_cub *cub, t_img *img, t_vector size);
void	xpm_to_image(t_cub *cub, t_img *img, char *xpm);

#endif