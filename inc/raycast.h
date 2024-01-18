/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:36:59 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/18 19:02:49 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>
# include "ansi_hex_codes.h"
# include "../libft/include/libft.h"
# include "cub3d.h"

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
# define COLL_SENS 0.3
# define SOME_LARGE_VALUE 1000000
# define HIT_POS_OFFSET 3.79

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
	int				direction;
	int				x_inc;
	int				y_inc;	
	int				wall_height;
	int				scale;
	int				length;
	int				neg_size;
	int				max;
	int				step;
	int				hit;
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
	int				direction;
	float			x_prev;
	float			y_prev;
}	t_player;

typedef struct s_raycast
{
	int					map_x;
	int					map_y;
	int					map_pos;
	int					max_depth;
	int					direction;
	int					hit;
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
	int					hit;
	int					*map;
	bool				door;
	float				line_height;
	float				line_offset;
	float				target_line_height;
	float				x_scale;
	float				y_scale;
	float				fisheye;
	float				min_distance;
	float				hit_pos;
	float				angle;
	struct s_txtr		pepe;
	struct s_txtr		walltest;
	struct s_txtr		brick;
	struct s_txtr		stone;
	struct s_txtr		wood;
	struct s_txtr		grass;
	struct s_txtr		metal;
	struct s_txtr		wall1;
	struct s_txtr		wall2;
	struct s_txtr		wall3;
	struct s_txtr		wall4;
	struct s_txtr		wall5;
	struct s_txtr		wall6;
	struct s_txtr		wall7;
	struct s_txtr		wall8;
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
void	set_texture(t_data *data, t_txtr *texture);
void	set_shortest_line_vars(t_data *data, float min, t_line line, float hit);

//math_utils
void	normalize_angle(float *angle, float increment);
void	calculate_distance(t_data *data, t_line line1, t_line line2);
float	dist(t_line line);

//drawing_utils
void	put_pixel(t_data *data, int x, int y, int color);
t_line	draw_rays_horizontal(t_data *data, float angle);
void	draw_circle(t_data *data, int x, int y, int size);
void	draw_line(t_data *data, t_line line, int color, int size);
void	draw_background(t_data *data);

//memory management/mlx
void	start_game(t_data *data);
void	initialize_textures(t_data *data);
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