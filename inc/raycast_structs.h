/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:23:07 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/22 17:09:10 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_STRUCTS_H
# define RAYCAST_STRUCTS_H

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
	int						ceiling_color;
	int						floor_color;
	int						map_width;
	int						map_height;
	int						map_size;
	int						line_color;
	int						hit;
	int						*map;
	bool					door;
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
}	t_data;

#endif