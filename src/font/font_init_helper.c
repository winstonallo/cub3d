/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_init_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 23:07:48 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/18 01:47:36 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/font.h"

void	font_free_images(t_font *font, int i)
{
	while (i > 0)
	{
		free(font->xl_font.letter[i].img);
		i--;
	}
}

void	del_font(void *mlx, t_font *font, int type)
{
	int	i;

	i = 0;
	while (i < 26)
	{
		if (type == 4)
			mlx_destroy_image(mlx, font->xl_font.letter[i++].img);
		else if (type == 3)
			mlx_destroy_image(mlx, font->big_font.letter[i++].img);
		else if (type == 2)
			mlx_destroy_image(mlx, font->medium_font.letter[i++].img);
	}
}

void	save_quit_extend(void *mlx, t_font *font, int err_code, int filter)
{
	int	i;

	i = 0;
	if (err_code == 3)
	{
		if (filter == 4)
			while (i < font->xl_font.del)
				mlx_destroy_image(mlx, font->xl_font.letter[i++].img);
		if (filter == 3)
			while (i < font->big_font.del)
				mlx_destroy_image(mlx, font->big_font.letter[i++].img);
		if (filter == 4)
			while (i < font->medium_font.del)
				mlx_destroy_image(mlx, font->medium_font.letter[i++].img);
		if (filter == 4)
			while (i < font->small_font.del)
				mlx_destroy_image(mlx, font->small_font.letter[i++].img);
	}
}

void	save_quit(void *mlx, t_font *font, int err_code, int filter)
{
	int	i;

	if (err_code == -1)
		return ;
	i = 0;
	if (err_code == -2)
	{
		if (filter == 4)
			while (i < font->xl_font.del - 1)
				mlx_destroy_image(mlx, font->xl_font.letter[i++].img);
		if (filter == 3)
			while (i < font->big_font.del - 1)
				mlx_destroy_image(mlx, font->big_font.letter[i++].img);
		if (filter == 4)
			while (i < font->medium_font.del - 1)
				mlx_destroy_image(mlx, font->medium_font.letter[i++].img);
		if (filter == 4)
			while (i < font->small_font.del - 1)
				mlx_destroy_image(mlx, font->small_font.letter[i++].img);
	}
	if (err_code == -3)
		save_quit_extend(mlx, font, err_code, filter);
	free(font);
}
