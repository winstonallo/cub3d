/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:46:06 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/25 20:31:23 by yannis           ###   ########.fr       */
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

typedef struct s_temp t_temp;

typedef struct s_button
{
	t_img	*img;
	int		del;
	int		iden;
	int		activate;
	int		posx;
	int		posy;
	int		button_clicked;
	int		(*function)(t_temp *, int i);
}				t_button;

typedef struct s_temp
{
	void		*mlx;
	void		*win;
	t_button	**button;
	int			button_index;
	int			clicked;
}				t_temp;

t_button	*button_init(void *mlx, char *path);
void		matrix_free(char **arr);
void		button_delete(t_button *button, void *mlx);
int			load_button(t_button *button, void *mlx, char *path);
int			click(void *temp);
int			button_add_function(int (*function)(t_temp *, int), t_temp *game, int i);
int			button_change_position(t_temp *game, int posx, int posy, int iden);
int			int_exit(t_temp *temp, int i);
int			say(t_temp *temp, int i);
int			button_animation(void *data);

void		free_game(t_temp *game);

#endif