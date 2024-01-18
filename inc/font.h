/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:01:25 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/18 03:22:20 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

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
	int				color;
}	t_txtr;



typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}				t_color;

typedef struct s_font_inner
{
	t_txtr	*letter;
	int		del;
}				t_font_inner;

typedef struct s_font
{
	t_font_inner	xl_font;
	t_font_inner	big_font;
	t_font_inner	medium_font;
	t_font_inner	small_font;
}				t_font;

typedef struct s_cords
{
	int	copy_x;
	int	copy_y;
	int	img_x;
	int	img_y;
}				t_cords;

typedef struct s_data t_data;

typedef struct s_button
{
	t_txtr	*img;
	int		del;
	int		curr;
	int		iden;
	int		active;
	int		activate;
	int		posx;
	int		posy;
	int		button_clicked;
	int		(*function)(t_data *, int i);
}				t_button;

typedef struct s_gif
{
	t_txtr	*img;
	t_txtr	*display;
	int		posx;
	int		posy;
	int		curr;
	int		del;
}				t_gif;


typedef struct s_font_setting
{
	int	x;
	int	y;
	int	color;
	int	identifier;
}				t_font_setting;



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
	int					gifs;
	int					button_index;
	int					clicked;
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
	struct s_gif		**gif;
	struct s_button		**button;
	struct s_font		*font;
	struct s_cords		cords;
}	t_data;

// font init functions //
t_font	*font_init_master(void *mlx);
int		load_font(void *mlx, t_font *font, char **names);

// font write functions //
int		font_write_master(char *w, t_data *game, t_font_setting f);
int		font_write_to_im_master(char *w, t_data *g, t_txtr *c, t_font_setting s);
void	font_to_lower(char *word);
void	*font_create_new_image(char *word, t_data *game, int identifier);
void	font_write_to_image(t_data *ga, t_txtr *t, char *to, t_font_setting fo);
void	font_write_to_display(t_data *ga, char *to, t_font_setting fo);
void	free_array(char **name);

// font helper functins //
void	del_font(void *mlx, t_font *font, int type);
void	save_quit_extend(void *mlx, t_font *font, int err_code, int filter);
void	save_quit(void *mlx, t_font *font, int err_code, int filter);
void	font_free_images(t_font *font, int i);

// image edit functions //
void	image_edit(t_data *game, t_txtr *base, t_txtr to_copy, int identifier);
#endif