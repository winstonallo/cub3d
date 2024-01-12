/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:36:59 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/12 21:39:47 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <stdio.h>
# include <stdlib.h>
# include "../minilibx-mac/mlx.h"
# include <math.h>
# include <stdbool.h>
# include "../libft/include/libft.h"
# include "cub3d.h"

# define GREEN		"\e[92;5;118m"
# define RED 		"\e[91m"
# define YELLOW 	"\e[93;5;226m"
# define GRAY		"\e[33;2;37m"
# define RESET 		"\e[0m"
# define CURSIVE 	"\e[33;3m"
# define BOLD 		"\e[1m"

# define HEXA_RED	0x00FF0000
# define HEXA_GREEN	0x0000FF00
# define HEXA_BLUE	0x000000FF
# define HEXA_WHITE	0x00FFFFFF
# define HEXA_BLACK	0x00000000
# define HEXA_YELLOW 0x00FFFF00
# define HEXA_GRAY	0x00A9A9A9
# define HEXA_PURPLE 0x00FF00FF
# define HEXA_CYAN	0x0000FFFF
# define HEXA_ORANGE 0x00FFA500
# define HEXA_PINK	0x00FFC0CB
# define HEXA_BROWN	0x00A52A2A
# define HEXA_GOLD	0x00FFD700
# define HEXA_SILVER 0x00C0C0C0
# define HEXA_BRONZE 0x00CD7F32
# define HEXA_LIME	0x00BFFF00
# define HEXA_OLIVE	0x00808000
# define HEXA_NAVY	0x00008080
# define HEXA_TEAL	0x00008080
# define HEXA_MAROON 0x00800000
# define HEXA_INDIGO 0x004B0082
# define HEXA_TURQUOISE 0x0040E0D0
# define HEXA_VIOLET 0x00EE82EE
# define HEXA_BEIGE 0x00F5F5DC
# define HEXA_AQUA 0x0000FFFF
# define HEXA_CORAL 0x00FF7F50
# define HEXA_SKY_BLUE 0x0087CEEB
# define HEXA_MINT 0x00F5FFFA
# define HEXA_LAVENDER 0x00E6E6FA
# define HEXA_TAN 0x00D2B48C
# define HEXA_SALMON 0x00FA8072
# define HEXA_KHAKI 0x00F0E68C
# define HEXA_CRIMSON 0x00DC143C
# define HEXA_ORCHID 0x00DA70D6

//constants
# define PI 3.1415926535
# define P2 1.570796327
# define P3 4.71238898
# define MAX_DISTANCE 1000
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000
# define SCREEN_HEIGHT2 500
# define SPEED 0.03
# define TURN_SPEED 10
# define DR 0.00872665
# define FIELD_OF_VIEW 1.04719755
# define MAX_DIST 1000000
# define WALL_HEIGHT 1.2
# define COLL_SENS 0.1
# define SOME_LARGE_VALUE 1000000

//keys
# define ESCAPE 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define Q 113

typedef enum s_scale
{
	MAPSIZE,
	SCREEN
}	t_scale;

typedef enum s_ray
{
	VERTICAL,
	HORIZONTAL
}	t_ray;

typedef enum s_dir
{
	NO_DIR,
	NORTH,
	SOUTH,
	EAST,
	WEST,
	NORTH_EAST,
	NORTH_WEST,
	SOUTH_EAST,
	SOUTH_WEST
}	t_dir;

typedef enum s_move
{
	DOWN,
	UP,
	TURN_LEFT,
	TURN_RIGHT,
	STRAFE_RIGHT,
	STRAFE_LEFT
}	t_move;

typedef enum s_error
{
	SUCCESS,
	NO_WALL_HIT
}	t_error;

typedef struct s_dist
{
	float			y0;
	float			x0;
	float			x1;
	float			y1;
}	t_dist;

typedef struct s_img
{
	char			*addr;
	int				bpp;
	int				l_l;
	int				endian;
}	t_img;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
}	t_mlx;

typedef struct s_line
{
	float			x0;
	float			y0;
	float			x1;
	float			y1;
	float			x_step;
	float			y_step;
	int				wall_height;
	int				scale;
	int				length;
	int				neg_size;
	int				max;
	int				step;
}	t_line;

typedef struct s_player
{
	float			x_pos;
	float			y_pos;
	int				x_screen_pos;
	int				y_screen_pos;
	float			angle;
	float			x_dir;
	float			y_dir;
}	t_player;

typedef struct s_raycast
{
	int					map_x;
	int					map_y;
	int					map_pos;
	int					max_depth;
	float				reach_x;
	float				reach_y;
	float				angle;
	float				inc_x;
	float				inc_y;
	float				a_tan;
	float				n_tan;
	struct s_dist		dist;
}	t_raycast;

typedef struct s_txtr
{
	void			*img;
	char			*addr;
	int				bpp;
	int				l_l;
	int				endian;
	int				width;
	int				height;
}	t_txtr;

typedef struct s_data
{
	int					view_dir;
	int					ceiling_color;
	int					floor_color;
	int					map_width;
	int					map_height;
	int					map_size;
	int					win_width;
	int					win_height;
	int					line_color;
	float				line_height;
	float				line_offset;
	float				target_line_height;
	float				x_scale;
	float				y_scale;
	float				fisheye;
	float				min_distance;
	float				hit_pos;
	float				angle;
	int					hit;
	int					*map;
	struct s_txtr		pepe;
	struct s_txtr		brick;
	struct s_txtr		stone;
	struct s_txtr		wood;
	struct s_txtr		grass;
	struct s_txtr		metal;
	struct s_player		player;
	struct s_mlx		mlx;
	struct s_img		img;
	struct s_line		shortest_line;
}	t_data;

//init
void	set_data_view(t_data *data);

//map
void	draw_map(t_data *data);
void	draw_player(t_data *data);
void	initialize_data(t_data *data);
int		isdirection(char c);
void	set_directions(t_data *data);

//raycaster
void	raycast(t_data *data);
void	get_3d_line(t_line *line1, int i, t_data *data);
void	adjust_vars(t_data *data, float angle);
void	init_vars_horizontal(t_raycast *h_ray, t_player *player, float angle);
void	get_line(t_line *line, t_raycast ray, t_data *data);
void	scan(t_raycast *ray, t_data *data, int max);
void	init_vars_vertical(t_raycast *v_ray, t_player *player, float angle);
void	draw_texture(t_data *data, int x, t_line line, t_txtr *texture);
bool	collision(t_data *data, float new_x, float new_y);

//math_utils
float	normalize_angle(float angle, float increment);
void	calculate_distance(t_data *data, t_line line1, t_line line2);
float	dist(t_line line);

//drawing_utils
void	put_pixel(t_data *data, int x, int y, int color);
t_line	draw_rays_horizontal(t_data *data, float angle);
void	draw_circle(t_data *data, int x, int y, int size);
void	draw_line(t_data *data, t_line line, int color, int size);
void	draw_background(t_data *data);

//memory management
void	exit_failure(t_data *data, char *msg);
int		exit_success(t_data *data);
void	new_image(t_data *data);

//tests
int		*get_map(void);
int		print_test_raycasting(t_data *data, int loopbreak, int direction,
			t_raycast *ray);
// void	print_test(t_data *data, int color, int value, int x, int y);

//game
int		event(int key, t_data *data);
void	init_line(t_line *line, t_data *data, int length);

#endif