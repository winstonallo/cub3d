/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:36:59 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/29 19:16:58 by abied-ch         ###   ########.fr       */
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
# include "constants.h"
# include "raycast_structs.h"
# include "../libft/include/libft.h"
# include "cub3d.h"
# include "constants.h"
# include "raycast_structs.h"

//map
void		draw_map(t_data *data);
void		draw_player(t_data *data);
void		data_init(t_data *data);
int			isdirection(char c);
void		set_directions(t_data *data);
bool		is_not_wall(int a, int b, int c, int d);
void		get_texture_data(t_txtr *t, t_data *data, char *path);
void		set_map_scale(t_data *data);
void		vertical_vars_init(t_raycast *v_ray, t_player *p, double angle);
void		horizontal_vars_init(t_raycast *h_ray, t_player *p, double angle);
void		scan(t_raycast *ray, t_data *data, int max);
int			mpl(char *map);

//raycaster
void		raycast(t_data *data);
void		get_3d_line(t_line *line1, int i, t_data *data);
void		adjust_vars(t_data *data, double angle);
void		get_line(t_line *line, t_raycast ray, t_data *data);
void		draw_texture(t_data *data, int x, t_line line, t_txtr *texture);
bool		collision(t_data *data, double new_x, double new_y);
void		set_texture(t_data *data, t_txtr *texture);
void		set_shortest_line(t_data *data, double min, t_line l, double hit);
void		set_scaling_factor(t_data *data);

//math_utils
void		normalize_angle(double *angle, double increment);
void		calculate_distance(t_data *data, t_line line1, t_line line2);
double		dist(t_line line);
bool		is_inside_circle(int x, int y, int size);
void		set_line_vars(t_line *line, int size);
void		scale_line_to_minimap(t_line *line, t_data *data);

//drawing_utils
void		put_pixel(t_data *data, int x, int y, int color);
void		draw_circle(t_data *data, int x, int y, int size);
void		draw_line(t_data *data, t_line line, int color, int size);
void		draw_background(t_data *data);

//memory management/mlx
void		start_game(t_data *data);
void		textures_init(t_data *data);
void		exit_failure(t_data *data, char *msg);
int			exit_success(t_data *data);
void		exit_error(char *msg, t_data *data);
void		new_image(t_data *data);
void		free_textures(t_data *data);
void		check_argument_count(int argc);

//game
int			event(int key, t_data *data);
void		init_line(t_line *line, t_data *data, int length);

//map
int			*map(char *map, t_data *data);
int			map_get_player_pos(int *map);
t_texture	map_get_textures(char *map);
int			replace(char *fname, char *pos, char *content);
void		start_game(t_data *data);

#endif
