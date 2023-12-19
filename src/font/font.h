/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:01:25 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/19 23:40:35 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../../../libft/libft.h"

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

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_font	*font;
	t_cords	cords;
}				t_game;

// font init functions //
t_font	*font_init(void *mlx);
int		load_font(void *mlx, t_font *font, char **names);

// font write functions //
int		font_write(char *word, t_game *game, t_img *copy, int dientifier);
void	font_to_lower(char *word);
void	*font_create_new_image(char *word, t_game *game, int identifier);
void	font_write_to_image(t_game *game, t_img *temp, char *to_write, int ide);
void	free_array(char **name);

// font helper functins //
void	del_font(void *mlx, t_font *font, int type);
void	save_quit_extend(void *mlx, t_font *font, int err_code, int filter);
void	save_quit(void *mlx, t_font *font, int err_code, int filter);
void	free_images(t_font *font, int i);

// image edit functions //
void	image_edit(t_game *game, t_img *base, t_img to_copy, int identifier);

#endif