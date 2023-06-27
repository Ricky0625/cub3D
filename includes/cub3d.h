/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:32:46 by wricky-t          #+#    #+#             */
/*   Updated: 2023/06/27 12:01:57 by wxuerui          ###   ########.fr       */
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
# define WIN_WIDTH 1280
// # define WIN_WIDTH 320
# define WIN_HEIGHT 768
// # define WIN_HEIGHT 200
# define MM_TILE_SIZE 20
# define MM_SIZE 10 // in number of tiles
# define MM_COLOR_WALL 0x00d5d6ea
# define MM_COLOR_FLOOR 0x00f6f6eb
# define MM_COLOR_VOID 0x0025131A
# define MM_COLOR_PLAYER 0x0052dee5
# define MM_COLOR_RAY 0x00bffcc6

// RAYCASTING ENVIRONMENT MACROS
# define FOV 60 // in degrees
# define FOV_MIN 10
# define FOV_MAX 170
# define CENTER_OFFSET_MAX 50
# define GRID_SIZE 64

// PLAYER RELATED MACROS
# define PLY_DIR "NSWE"
# define MOVE_SPEED 10
// NOTE: 5 is 5 units in unit coord, not grid coord
# define TURN_SPEED 0.1
// NOTE: 0.1 is 0.1 radian
# define FOV_STEP 2
// NOTE: 5 is 5 degrees
# define CENTER_OFFSET_STEP 5
// NOTE: 5 is 5 units in unit coord, not grid coord

// MAP RELATED MACROS
# define MAP_CHARS "10NSWE "
# define WALL '1'
# define FLOOR '0'
# define EMPTY ' '

/* ====== ENUMS ====== */

/**
 * @brief Enum for control key's keycodes.
 * @attention It's for macos only.
 * 
 * @details
 * W - move up
 * A - move left
 * S - move down
 * D - move right
 * F - toggle fisheye effect
 * M - toggle minimap
 * Q - look up
 * E - look down
 * R - reset raycasting environment
 * + - increase FOV
 * - - decrease FOV
 * ESC - exit
 * LEFT - turn left
 * RIGHT - turn right
 * LSHIFT - toggle mouse (use mouse to rotate player viewing angle)
*/
typedef enum e_controls
{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_F = 3,
	KEY_M = 46,
	KEY_Q = 12,
	KEY_E = 14,
	KEY_R = 15,
	KEY_PLUS = 24,
	KEY_MINUS = 27,
	KEY_LSHIFT = 257,
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

typedef struct s_ray
{
	t_vector	p_intersection;
	double		dist;
	double		angle;
}	t_ray;

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
	double		viewing_angle;
	t_vector	grid_pos;
	t_vector	unit_pos;
	t_vector_d	displacement;
}	t_player;

typedef struct s_projection_attr
{
	double		dist_to_plane;
	double		ray_angle_step;
	int			fov;
	int			center_offset;
	t_vector	center_pos;
	double		mm_scale;
}	t_projection_attr;

typedef struct s_render_option
{
	int	fisheye;
	int	minimap;
	int	using_mouse;
}	t_render_option;

/**
 * @brief The main struct for Cub3D.
*/
typedef struct s_cub
{
	void				*mlx;
	void				*win;
	t_img				buffer;
	t_texture			textures;
	t_map				map;
	t_player			player;
	t_projection_attr	proj_attr;
	t_render_option		render_opt;
	t_ray				rays[WIN_WIDTH];
}	t_cub;

/* ====== FUNCTION PROTOTYPES ====== */

// FUNCTION RELATED MACROS
typedef void	(*t_map_iterator_func)(t_cub *cub, int row, int column);

// Init
void	init_textures(t_texture *texture);
void	init_projection_attribute(t_projection_attr *proj_attr);
void	init_render_option(t_render_option *render_opt);
void	init_player(t_player *player);
void	set_player_initial_state(t_cub *cub, int row, int column);

// Raycasting
t_ray	get_ray(t_cub *cub, double angle);
void	store_rays_to_cub(t_cub *cub);

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

// Mouse Controls
void	toggle_mouse(t_cub *cub);
int		mouse_hook(int x, int y, t_cub *cub);

// Controls
void	adjust_fov(t_cub *cub, int key);
void	adjust_center_offset(t_cub *cub, int key);
void	change_raycasting_option(t_cub *cub, int key);
void	reset_raycasting_environment(t_cub *cub);

// Movement
void	move_player(t_cub *cub, t_controls key);
void	rotate_player(t_cub *cub, t_controls key, double angle);

// Minimap
void	render_minimap(t_cub *cub);

// Utils
int		create_argb(unsigned char color[4]);
u_char	get_a(int argb);
void	print_color(t_cub *cub, unsigned char color[4]);
int		show_error(char *err);
void	exit_cub(t_cub *cub, char *err);
void	validate_map(t_cub *cub, int row, int column);
double	deg_to_rad(double deg);
double	rad_to_deg(double rad);

// Render
void	render_world(t_cub *cub);

// Map utils
void	map_iterator(t_cub *cub, t_map_iterator_func f, t_iterate_type type);

// Draw utils
void	draw_pixel(t_cub *cub, int x, int y, int color);
void	draw_line(t_cub *cub, t_vector p1, t_vector p2, int color);
void	draw_triangle(t_cub *cub, t_vector *vects, int color, int fill);
void	brehensam_algo(t_vector *p, t_vector delta, t_vector dir, int *error);

// Math utils
double	get_distance(t_vector p1, t_vector p2);
int		int_abs(int num);
double	deg_to_rad(double deg);
double	rad_to_deg(double rad);

// Raycasting Utils
int		is_wall(t_cub *cub, t_vector p);
int		dda(t_cub *cub, t_vector *p, t_vector displacement);

#endif
