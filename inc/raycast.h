/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:36:59 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/23 21:16:38 by abied-ch         ###   ########.fr       */
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

//init
void	set_data_view(t_data *data);

//map
void	draw_map(t_data *data);
void	draw_player(t_data *data);
void	data_init(t_data *data, int argc);
int		isdirection(char c);
void	set_directions(t_data *data);
bool	is_not_wall(int a, int b, int c, int d);

//raycaster
void	raycast(t_data *data);
void	get_3d_line(t_line *line1, int i, t_data *data);
void	adjust_vars(t_data *data, float angle);
void	get_line(t_line *line, t_raycast ray, t_data *data);
void	draw_texture(t_data *data, int x, t_line line, t_txtr *texture);
bool	collision(t_data *data, float new_x, float new_y);
void	set_texture(t_data *data, t_txtr *texture);
void	set_shortest_line_vars(t_data *data, float min, t_line line, float hit);

//math_utils
void	normalize_angle(float *angle, float increment);
void	calculate_distance(t_data *data, t_line line1, t_line line2);
float	dist(t_line line);
bool	is_inside_circle(int x, int y, int size);
void	set_line_vars(t_line *line, int size);
void	scale_line_to_minimap(t_line *line);



//drawing_utils
void	put_pixel(t_data *data, int x, int y, int color);
t_line	draw_rays_horizontal(t_data *data, float angle);
void	draw_circle(t_data *data, int x, int y, int size);
void	draw_line(t_data *data, t_line line, int color, int size);
void	draw_background(t_data *data);

//memory management/mlx
void	start_game(t_data *data);
void	textures_init(t_data *data);
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

//lift
int	elevator_init(t_data *data);

//map
int			*map(char *map, t_data *data);
int			map_get_player_pos(int *map);
t_txtr		map_get_textures(char *map);
int			replace(char *fname, char *pos, char *content);

//font
t_font			*font_init(void *mlx);
int				font_write(char *word, t_data *game, t_font_setting f_setting);
int				font_write_img(char *w, t_data *g, t_txtr *c, t_font_setting f);
t_font_setting	font_settings(int posx, int posy, int color, int identifier);
void			font_delete(t_data *game);

//buttons
int			*button_init(t_data *game, char *path, int (*f)(t_data *, int));
void		button_delete(t_data *game, void *mlx);
int			button_change_function(int (*f)(t_data *, int i), t_data *game, int i);
int			button_change_position(t_data *game, int posx, int posy, int iden);
int			button_switch(t_data *game, int i);
int			say(t_data *temp, int i);
int			int_exit(t_data *game, int i);
int			button_animation(void *data);
int			button_loop(t_data *game);

//gif
void		gif_loop(t_data *game);
void		gif_delete(t_data *game, void *mlx);
int			gif_init(t_data *game, char *path, int posx, int posy);

//image_edit
void		image_edit(t_data *g, t_txtr *base, t_txtr to_copy, int identifier);

void	start_game_f_b_g(t_data *data);
void	start_game(t_data *data);
// int	loop(void *data);

#endif
