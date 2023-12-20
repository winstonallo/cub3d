/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:36:59 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/20 22:21:22 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include "../libft/include/libft.h"

# define GREEN		"\e[92;5;118m"
# define RED 		"\e[91m"
# define YELLOW 	"\e[93;5;226m"
# define GRAY		"\e[33;2;37m"
# define RESET 		"\e[0m"
# define CURSIVE 	"\e[33;3m"
# define BOLD 		"\e[1m"

//constants
# define PI 3.1415926535
# define P2 1.570796327
# define P3 4.71238898
# define MAX_DISTANCE 1000
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000
# define SCREEN_HEIGHT2 500
# define SPEED 0.02
# define DR 0.00872665
# define FIELD_OF_VIEW 1.04719755
# define MAX_DIST 1000000
# define WALL_HEIGHT 1.2
# define COLL_SENS 0.1

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
	int				scale;
	int				thickness;
	int				length;
	int				neg_size;
	float			x_step;
	float			y_step;
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
	int					loop_protection;
	int					r;
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
	float				vertical_distance;
	float				horizontal_distance;
	struct s_dist		dist;
}	t_raycast;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				bpp;
	int				l_l;
	int				endian;
	int				width;
	int				height;
}	t_texture;

typedef struct s_data
{
	int					error;
	int					view_dir;
	int					map_width;
	int					map_height;
	int					map_size;
	int					win_width;
	int					win_height;
	int					wall_color;
	int					floor_color;
	int					player_color;
	int					line_color;
	int					*map;
	float				line_height;
	float				line_offset;
	float				target_line_height;
	float				tile_width;
	float				tile_height;
	float				min_distance;
	float				x_scale;
	float				y_scale;
	float				scale_factor;
	float				fisheye;
	struct s_texture	brick;
	struct s_texture	stone;
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

//math
void	raycast(t_data *data);
void	get_3d_line(t_line *line1, int i, t_data *data);
void	adjust_vars(t_data *data, float angle);
void	init_vars_horizontal(t_raycast *h_ray, t_player *player, float angle);
void	get_line(t_line *line, t_raycast ray, t_data *data);
void	calculate_distance(t_data *data, t_line line1, t_line line2);
void	scan(t_raycast *ray, t_data *data);
void	init_vars_vertical(t_raycast *v_ray, t_player *player, float angle);

//drawing_utils
void	put_pixel(t_data *data, int x, int y, int color);
t_line	draw_rays_horizontal(t_data *data, float angle);
void	draw_circle(t_data *data, int x, int y, int size);
void	draw_line(t_data *data, t_line line, int color, int size);

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