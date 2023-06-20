/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:32:46 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/20 21:36:15 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ====== LIBRARIES ====== */
# include <mlx.h>
# include <error.h>
# include <lib42.h>
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
# define WIN_WIDTH 1280 // Projection plane width
# define WIN_HEIGHT 768 // Projection plane height
# define GRID_SIZE 64
# define MM_WIDTH 360
# define MM_HEIGHT 270
# define MM_SPT_SIZE 15
# define MM_WALL 0x00B8B8B8
# define MM_FLOOR 0x002E3357
# define MM_VOID 0x0025131A

// RAYCASTING ENVIRONMENT MACROS
# define FOV 60 // in degrees

// PLAYER RELATED MACROS
# define PLY_DIR "NSWE"
# define MOVE_SPEED 10 // NOTE: 10 is 10 units in unit coord, not grid coord
# define TURN_SPEED 0.1 // NOTE: 0.1 is 0.1 radian

// MAP RELATED MACROS
# define MAP_CHARS "10NSWE "
# define WALL '1'
# define FLOOR '0'
# define EMPTY ' '

/* ====== ENUMS ====== */

/**
 * @brief Enum for control key's keycodes.
 * @attention It's for macos only.
*/
typedef enum e_controls
{
	KEY_W = 13, // forward
	KEY_A = 0, // turn left
	KEY_S = 1, // backward
	KEY_D = 2, // turn right
	KEY_ESC = 53,
	KEY_LEFT = 123,
	KEY_RIGHT = 124
}	t_controls;

typedef enum e_dir
{
	NORTH = 'N',
	SOUTH = 'S',
	WEST = 'W',
	EAST = 'E',
	UNDEFINED
}	t_dir;

typedef enum e_rgba
{
	A,
	R,
	G,
	B,
	TOTAL_RGBA
}	t_rgba;

typedef enum e_element
{
	NO,
	SO,
	WE,
	EA,
	C,
	F,
	UNKNOWN
}	t_element;

typedef enum e_iterate_type
{
	ROW,
	COLUMN
}	t_iterate_type;

typedef enum e_orientaion
{
	HORIZONTAL,
	VERTICAL
}	t_orientation;

/* ====== STRUCTS ====== */

/**
 * @brief Vector (x, y)
*/
typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_vector_d
{
	double	x;
	double	y;
}	t_vector_d;

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
 * @brief Store value of RGBA
*/
typedef struct s_color
{
	unsigned char	color[TOTAL_RGBA];
}	t_color;

/**
 * @brief Store all the info about the texture
*/
typedef struct s_texture
{
	t_img	no_tex;
	t_img	so_tex;
	t_img	we_tex;
	t_img	ea_tex;
	t_img	mm_wall;
	t_img	mm_floor;
	t_img	mm_player;
	int		ceil_set;
	int		ceil;
	int		floor_set;
	int		floor;
}	t_texture;

/**
 * @brief Map data
 * 
 * @attention size.x is width, size.y is height
*/
typedef struct s_map
{
	t_list		*info_list;
	t_vector	size;
	char		**map;
}	t_map;

/**
 * @brief Player data
*/
typedef struct s_player
{
	t_dir		dir;
	double		viewing_angle; // should be in radian
	t_vector	grid_pos; // grid coordinate
	t_vector_d	unit_pos; // unit coordinate
	t_vector_d	displacement; // displacement from the grid coordinate
}	t_player;

typedef struct	s_projection_attr
{
	double		dist_to_proj_plane; // distance to the projection plane
	double		ray_angle_step; // angle between subsequent rays
}	t_projection_attr;

typedef struct	s_ray
{
	t_vector	intersection_point; // first will be used by the first intersection, then the checkpoints (unit coord)
	double		dist; // distance of the ray (assuming now it's not the "corrected" ray distance)
}	t_ray;

/**
 * @brief The main struct for Cub3D.
*/
typedef struct s_cub
{
	void				*mlx;
	void				*win;
	t_img				buffer;
	t_img				minimap;
	t_texture			textures;
	t_map				map;
	t_player			player;
	t_projection_attr	proj_attr;
	t_ray				rays[WIN_WIDTH];
}	t_cub;

/* ====== FUNCTION PROTOTYPES ====== */

// FUNCTION RELATED MACROS
typedef void	(*t_map_iterator_func)(t_cub *cub, int row, int column);

// Init
void	init_textures(t_texture *texture);
void	init_projection_attribute(t_projection_attr *proj_attr);
void	init_step_size(t_vector_d *step_size, double angle, t_step_type type);
void	init_player(t_player *player);
void	set_player_initial_state(t_cub *cub, int row, int column);

// hook
void	cub3d_hooks(t_cub *cub);
int		key_hook(int key, t_cub *cub);
int		close_cub(t_cub *cub);

// Img utils
void	new_image(t_cub *cub, t_img *img, t_vector size);
void	xpm_to_image(t_cub *cub, t_img *img, char *xpm);
void	copy_image(t_img *src, t_img *dst, t_vector dst_pos);
void	new_rect(t_cub *cub, t_img *img, t_vector size, int color);

// Parse Map
void	parse_map(t_cub *cub, char *map_name);
void	parse_elements(t_cub *cub, t_list **info_list);
int		is_map_content(char *str);
int		check_elements_all_set(t_texture *textures);
void	*llto2darr_func(void *content);
int		is_map_content(char *str);

// Movement
void	move_player(t_cub *cub, t_controls key);
void	rotate_player(t_cub *cub, t_controls key);

// Minimap
void	render_minimap(t_cub *cub);

// Utils
int		create_argb(t_cub *cub, unsigned char color[4]);
u_char	get_a(int argb, int endian);
void	print_color(t_cub *cub, unsigned char color[4]);
int		show_error(char *err);
void	exit_cub(t_cub *cub, char *err);
void	validate_map(t_cub *cub, int row, int column);
double	deg_to_rad(double deg);
double	rad_to_deg(double rad);

// Render
void	raycaster(t_cub *cub);

// Map utils
void	map_iterator(t_cub *cub, t_map_iterator_func f, t_iterate_type type);

#endif