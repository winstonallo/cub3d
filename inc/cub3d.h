/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:47:40 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/18 01:45:22 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/include/libft.h"

typedef struct s_texture
{
	char	*color_fds[2];
	int		texture_fds[4];
	int		err_code;
}				t_texture;

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
	t_font		*font;
	t_cords		cords;
}				t_game;

typedef struct s_font_setting
{
	int	x;
	int	y;
	int	color;
	int	identifier;
}				t_font_setting;

int			*map(char *map);
int			map_get_player_pos(int *map);
t_texture	map_get_textures(char *map);
int			replace(char *fname, char *pos, char *content);

t_font			*font_init(void *mlx);
int				font_write(char *word, t_game *game, t_font_setting f_setting);
int				font_write_img(char *w, t_game *g, t_img *c, t_font_setting f);
t_font_setting	font_settings(int posx, int posy, int color, int identifier);
void			font_delete(t_game *game);

// image edit //
// void	image_edit(t_game *g, t_img *base, t_img to_copy, int identifier);


/*	Buttons	*/
int			*button_init(t_game *game, char *path, int (*f)(t_game *, int));
void		button_delete(t_game *game, void *mlx);
int			button_change_function(int (*f)(t_game *, int i), t_game *game, int i);
int			button_change_position(t_game *game, int posx, int posy, int iden);
int			button_switch(t_game *game, int i);
int			say(t_game *temp, int i);
int			int_exit(t_game *game, int i);
int			button_animation(void *data);
int			button_loop(t_game *game);

/*	Gif	*/
void		gif_loop(t_game *game);
void		gif_delete(t_game *game, void *mlx);
int			gif_init(t_game *game, char *path, int posx, int posy);

/*	Image edit	*/
void		image_edit(t_game *g, t_img *base, t_img to_copy, int identifier);

#endif