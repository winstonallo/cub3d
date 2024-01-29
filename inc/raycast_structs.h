/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:15:16 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/29 19:02:15 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_STRUCTS_H
# define RAYCAST_STRUCTS_H

# include <time.h>

typedef struct s_check
{
	char	*str;
	int		change;
	int		valid;
	int		pos;
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
	double			y0;
	double			x0;
	double			x1;
	double			y1;
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
	double			x0;
	double			y0;
	double			x1;
	double			y1;
	double			x_step;
	double			y_step;
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
	double			x_pos;
	double			y_pos;
	double			x_oldpos;
	double			y_oldpos;
	int				x_screen_pos;
	int				y_screen_pos;
	double			angle;
	double			x_dir;
	double			y_dir;
	int				direction;
	double			x_prev;
	double			y_prev;
}	t_player;

typedef struct s_raycast
{
	int					map_x;
	int					map_y;
	int					map_pos;
	int					max_depth;
	int					direction;
	int					hit;
	double				reach_x;
	double				reach_y;
	double				angle;
	double				inc_x;
	double				inc_y;
	double				a_tan;
	double				n_tan;
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

typedef struct s_texture_base
{
	struct s_txtr		north;
	struct s_txtr		south;
	struct s_txtr		east;
	struct s_txtr		west;
}	t_texture_base;

typedef struct s_data
{
	int						view_dir;
	int						ceiling_color;
	int						floor_color;
	int						map_width;
	int						map_height;
	int						map_size;
	int						win_width;
	int						win_height;
	int						line_color;
	int						hit;
	int						floors;
	int						map_scale_x;
	int						map_scale_y;
	int						*map;
	char					*no_txtr;
	char					*so_txtr;
	char					*we_txtr;
	char					*ea_txtr;
	double					line_height;
	double					line_offset;
	double					target_line_height;
	double					x_scale;
	double					y_scale;
	double					fisheye;
	double					min_distance;
	double					hit_pos;
	double					angle;
	double					scaling;
	struct s_raycast		h_ray;
	struct s_raycast		v_ray;
	struct s_texture_base	textures;
	struct s_player			player;
	struct s_mlx			mlx;
	struct s_img			img;
	struct s_line			shortest_line;
}	t_data;

#endif