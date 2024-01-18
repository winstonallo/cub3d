/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:46:06 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/15 16:44:57 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTON_H
# define BUTTON_H

# define _POSIX_C_SOURCE 199309L

# include <mlx.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include "../../libft/include/libft.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bps;
	int		line_len;
	int		bits_per_pixel;
	int		endian;
	int		color;
}				t_img;

typedef struct s_game t_game;

typedef struct s_button
{
	t_img	*img;
	int		del;
	int		curr;
	int		iden;
	int		active;
	int		activate;
	int		posx;
	int		posy;
	int		button_clicked;
	int		(*function)(t_game *, int i);
}				t_button;

typedef struct s_gif
{
	t_img	*img;
	int		posx;
	int		posy;
	int		curr;
	int		del;
}				t_gif;

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

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_gif		**gif;
	int			gifs;
	int			button_index;
	int			clicked;
	t_button	**button;
}				t_game;

int			button_init_master(t_game *game, char *path, int (*f)(t_game *, int));
void		b_matrix_free(char **arr);
void		display_button(t_game *game, int i, int lap, int inc);
void		button_delete_master(t_game *game, void *mlx);
int			load_button(t_button *button, void *mlx, char *path);
int			button_add_function_master(int (*function)(t_game *, int), t_game *game, int i);
int			button_change_position_master(t_game *game, int posx, int posy, int iden);
int			button_animation_master(void *data);
int			button_switch_master(t_game *game, int i);
int			mouse_actions(int (*function)(t_game *, int i), t_game *game, int i);

void		free_game(t_game *game);

#endif