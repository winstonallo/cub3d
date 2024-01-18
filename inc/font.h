/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:01:25 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/18 01:49:50 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

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
}			t_img;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}				t_color;

typedef struct s_font_inner
{
	t_img	*letter;
	int		del;
}				t_font_inner;

typedef struct s_font
{
	t_font_inner	xl_font;
	t_font_inner	big_font;
	t_font_inner	medium_font;
	t_font_inner	small_font;
}				t_font;


// typedef struct s_texture
// {
// 	char	*color_fds[2];
// 	int		texture_fds[4];
// 	int		err_code;
// }				t_texture;

typedef struct s_cords
{
	int	copy_x;
	int	copy_y;
	int	img_x;
	int	img_y;
}				t_cords;

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
	t_img	*display;
	int		posx;
	int		posy;
	int		curr;
	int		del;
}				t_gif;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_gif		**gif;
	int			gifs;
	int			button_index;
	int			clicked;
	t_button	**button;
	t_font	*font;
	t_cords	cords;
}				t_game;

typedef struct s_font_setting
{
	int	x;
	int	y;
	int	color;
	int	identifier;
}				t_font_setting;

// font init functions //
t_font	*font_init_master(void *mlx);
int		load_font(void *mlx, t_font *font, char **names);

// font write functions //
int		font_write_master(char *w, t_game *game, t_font_setting f);
int		font_write_to_im_master(char *w, t_game *g, t_img *c, t_font_setting s);
void	font_to_lower(char *word);
void	*font_create_new_image(char *word, t_game *game, int identifier);
void	font_write_to_image(t_game *ga, t_img *te, char *to, t_font_setting fo);
void	font_write_to_display(t_game *ga, char *to, t_font_setting fo);
void	free_array(char **name);

// font helper functins //
void	del_font(void *mlx, t_font *font, int type);
void	save_quit_extend(void *mlx, t_font *font, int err_code, int filter);
void	save_quit(void *mlx, t_font *font, int err_code, int filter);
void	font_free_images(t_font *font, int i);

// image edit functions //
void	image_edit(t_game *game, t_img *base, t_img to_copy, int identifier);
#endif