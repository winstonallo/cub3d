/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:46:06 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/26 00:12:56 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTON_H
# define BUTTON_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include "../../libft/include/libft.h"
# include "../../minilibx-linux/mlx.h"

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
	int		iden;
	int		activate;
	int		posx;
	int		posy;
	int		button_clicked;
	int		(*function)(t_game *, int i);
}				t_button;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			button_index;
	int			clicked;
	t_button	**button;
}				t_game;

t_button	*button_init_master(void *mlx, char *path);
void		matrix_free(char **arr);
void		button_delete_master(t_button *button, void *mlx);
int			load_button(t_button *button, void *mlx, char *path);
int			button_add_function_master(int (*function)(t_game *, int), t_game *game, int i);
int			button_change_position_master(t_game *game, int posx, int posy, int iden);
int			button_animation_master(void *data);

void		free_game(t_game *game);

#endif