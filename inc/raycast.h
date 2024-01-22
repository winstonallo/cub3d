/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:36:59 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/22 15:23:23 by abied-ch         ###   ########.fr       */
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
# include "constants.h"
# include "raycast_structs.h"

//init
void	set_data_view(t_data *data);

//map
void	draw_map(t_data *data);
void	draw_player(t_data *data);
void	initialize_data(t_data *data);
int		isdirection(char c);
void	set_directions(t_data *data);
bool	is_not_wall(int a, int b, int c, int d);

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