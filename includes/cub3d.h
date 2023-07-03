/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:32:46 by wricky-t          #+#    #+#             */
/*   Updated: 2023/07/03 18:06:46 by wxuerui          ###   ########.fr       */
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
// # define WIN_WIDTH 640
# define WIN_HEIGHT 768
// # define WIN_HEIGHT 480
# define MANUAL_WIDTH 200
# define MANUAL_BG_COLOR 0x331E1E1E
# define MANUAL_TEXT_COLOR 0x00ffffff
# define MANUAL_LINE_HEIGHT 20
# define MANUAL_MAX_LINE_SIZE 50
# define MM_IMG_SIZE 200
# define MM_TILE_SIZE 20
# define MM_NUM_TILES 10
# define MM_COLOR_WALL 0x22d5d6ea
# define MM_COLOR_FLOOR 0x22f6f6eb
# define MM_COLOR_VOID 0x2225131A
# define MM_COLOR_PLAYER 0x2252dee5
# define MM_COLOR_RAY 0x22bffcc6

// RAYCASTING ENVIRONMENT MACROS
# define FOV 60
# define FOV_MIN 10
# define FOV_MAX 170
# define CENTER_OFFSET_MAX 50
# define GRID_SIZE 64

// PLAYER RELATED MACROS
# define PLY_DIR "NSWE"
# define MOVE_SPEED 6
// NOTE: 5 is 5 units in unit coord, not grid coord
# define TURN_SPEED 0.05
// NOTE: 0.1 is 0.1 radian
# define FOV_STEP 2
// NOTE: 5 is 5 degrees
# define CENTER_OFFSET_STEP 30
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
	KEY_R = 15,
	KEY_PLUS = 24,
	KEY_MINUS = 27,
	KEY_LSHIFT = 257,
	KEY_ESC = 53,
	KEY_TAB = 48,
	KEY_UP = 126,
	KEY_DOWN = 125,
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

typedef enum e_ortt
{
	HORIZONTAL,
	VERTICAL,
	NONE
}	t_ortt;

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

typedef struct s_ray
{
	t_vector_d	p_intersection;
	double		dist;
	double		angle;
	t_ortt		ray_ortt;
}	t_ray;

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
 * @brief Helper struct to draw textures
*/
typedef struct s_slice
{
	double	height;
	t_img	*texture;
	int		offset;
	int		des_start_y;
	int		des_end_y;
	double	tex_step;
}	t_slice;

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
	t_vector_d	unit_pos;
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

enum e_manual_arg_type
{
	COORDS,
	VALUE,
	BOOL
};

typedef union
{
	t_vector	coords;
	int			value;
}	t_manual_variable_arg;


typedef struct
{
	char					*prefix;
	t_manual_variable_arg		arg;
	char					*suffix;
	enum e_manual_arg_type	arg_type;
}	t_manual_args;

typedef struct s_render_option
{
	int	fisheye;
	int	minimap;
	int	using_mouse;
	int	manual;
	double	mouse_rotate_speed;
}	t_render_option;

typedef struct s_active_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	q;
	int	e;
	int	left;
	int	right;
	int	up;
	int	down;
}	t_active_key;

/**
 * @brief The main struct for Cub3D.
*/
typedef struct s_cub
{
	void				*mlx;
	void				*win;
	t_img				buffer;
	t_img				minimap;
	t_img				manual;
	t_texture			textures;
	t_active_key		active_key;
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
void	init_images(t_cub *cub);

// Raycasting
t_ray	get_ray(t_cub *cub, double angle);
void	store_rays_to_cub(t_cub *cub);

// hook
void	cub3d_hooks(t_cub *cub);
int		key_down_hook(int key, t_cub *cub);
int		key_up_hook(int key, t_cub *cub);
int		close_cub(t_cub *cub);
void	change_key_state(int key, t_cub *cub, int state);

// Img utils
void	new_image(t_cub *cub, t_img *img, t_vector size);
void	xpm_to_image(t_cub *cub, t_img *img, char *xpm);
void	put_color_to_image(t_img *img, int color, int size);

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
void	mm_draw_ray(t_img *img, t_vector p1, t_vector p2, int color);
void	mm_adjust_start_and_end(t_cub *cub, t_vector *start, t_vector *end);

// Utils
int		create_argb(unsigned char color[4]);
u_char	get_a(int argb);
u_char	get_r(int argb);
u_char	get_g(int argb);
u_char	get_b(int argb);
void	print_color(t_cub *cub, unsigned char color[4]);
int		show_error(char *err);
void	exit_cub(t_cub *cub, char *err);
void	validate_map(t_cub *cub, int row, int column);
double	deg_to_rad(double deg);
double	rad_to_deg(double rad);

// Render
void	render_world(t_cub *cub);
void	put_manual(t_cub *cub);

// Render utils
void	get_wall_texture(t_cub *cub, t_ray *ray, t_slice *slice);
void	get_tex_offset(t_ray *ray, t_slice *slice);

// Map utils
void	map_iterator(t_cub *cub, t_map_iterator_func f, t_iterate_type type);

// Draw utils
void	draw_pixel(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, t_vector p1, t_vector p2, int color);
void	draw_slice(t_cub *cub, t_slice *slice, int col_index);
void	draw_triangle(t_img *img, t_vector *vects, int color, int fill);
void	draw_vertical_line(t_cub *cub, t_vector start, int len, int color);
void	brehensam_algo(t_vector *p, t_vector delta, t_vector dir, int *error);

// Math utils
double	get_distance(t_vector_d p1, t_vector_d p2);
int		int_abs(int num);
double	deg_to_rad(double deg);
double	rad_to_deg(double rad);

// Raycasting Utils
int		is_wall(t_cub *cub, t_vector p);
int		dda(t_cub *cub, t_vector_d *p, t_vector_d displacement);

#endif
