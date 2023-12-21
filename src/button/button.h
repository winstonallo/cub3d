/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:46:06 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/21 14:26:45 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTON_H
# define BUTTON_H

# include <mlx.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
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
	int		color;
}				t_img;

typedef struct s_button
{
	t_img	*img;
	int		del;
	int		iden;
	int		posx;
	int		posy;
	int		button_clicked;
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
int			load_button(t_button *button, void *mlx, char *path);
void		matrix_free(char **arr);
int			click(void *temp);

#endif