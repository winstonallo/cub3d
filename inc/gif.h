/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 00:33:55 by yannis            #+#    #+#             */
/*   Updated: 2024/01/16 22:24:24 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GIF_H
# define GIF_H

# define _POSIX_C_SOURCE 199309L

# include <mlx.h>
# include <time.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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
}			t_img;

typedef struct s_gif
{
	t_img	*img;
	t_img	*display;
	int		posx;
	int		posy;
	int		curr;
	int		del;
}				t_gif;

typedef struct s_cords
{
	int	copy_x;
	int	copy_y;
	int	img_x;
	int	img_y;
}				t_cords;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_gif		**gif;
	int			gifs;
	t_cords		cords;
}				t_game;

void	image_edit(t_game *g, t_img *base, t_img to_copy, int identifier);
void	free_images(t_gif *gif, void *mlx, int amount);
int		identify_amount(char *path);
int		alloc_imgs(t_gif *gif, char *path, void *mlx);

#endif