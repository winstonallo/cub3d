/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:15:16 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/23 19:36:00 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_STRUCTS_H
# define RAYCAST_STRUCTS_H

# include <time.h>

typedef struct s_check
{
	char	*str;
	int		change;
	int		fd;
}				t_check;

typedef struct s_map
{
	int	stepper;
	int	total;
	int	fill;
	int	pos2;
	int	pos;
	int	nl;
}				t_map;

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
	float			x_oldpos;
	float			y_oldpos;
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
	int				color;
}	t_txtr;

typedef struct s_button_loop
{
	struct	timespec	start_time;
	struct	timespec	current_time;
	int					active;
	int					lap;
	int					inc;
	int					i;
	double				elapsed_time;
	int					status;
}				t_button_loop;

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
	t_txtr	display;
	int		active;
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

typedef struct s_elevator
{
	struct s_gif	*left_wall_down;
	struct s_gif	*left_wall_up;
	struct s_gif	*right_wall_down;
	struct s_gif	*right_wall_up;
	struct s_gif	*back_wall_down;
	struct s_gif	*back_wall_up;
	struct s_gif	door;
	int				current;
	int				stage;
	int				floor;
	int				active;
}				t_elevator;

typedef struct s_texture_base
{
	struct s_txtr		wall1;
	struct s_txtr		wall2;
	struct s_txtr		wall3;
	struct s_txtr		wall4;
	struct s_txtr		wall5;
	struct s_txtr		wall6;
	struct s_txtr		wall7;
	struct s_txtr		wall8;
}	t_texture_base;

typedef struct s_data
{
	int						view_dir;
	int						ceiling_color;
	int						floor_color;
	int						map_width_old;
	int						map_height_old;
	int						map_width;
	int						map_height;
	int						map_size;
	int						win_width;
	int						win_height;
	int						line_color;
	int						hit;
	int						floors;
	int						argc;
	int						**maps;
	int						*map;
	int						gifs;
	int						button_index;
	int						clicked;
	bool					door;
	double					scaling;
	float					line_height;
	float					line_offset;
	float					target_line_height;
	float					x_scale;
	float					y_scale;
	float					fisheye;
	float					min_distance;
	float					hit_pos;
	float					angle;
	struct s_texture_base	textures;
	struct s_player			player;
	struct s_mlx			mlx;
	struct s_img			img;
	struct s_line			shortest_line;
	struct s_gif			**gif;
	struct s_button			**button;
	struct s_font			*font;
	struct s_cords			cords;
	struct s_elevator		elev;
}	t_data;

#endif