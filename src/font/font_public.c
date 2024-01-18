/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_public.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:15:52 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/18 02:46:22 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

int	font_write_to_im_master(char *word, t_data *g, t_txtr *c, t_font_setting f);
int	font_write_master(char *word, t_data *g, t_font_setting f);
t_font	*font_init_master(void *mlx);
void	image_edit(t_data *g, t_txtr *base, t_txtr to_copy, int identifier);

t_font	*font_init(void *mlx)
{
	return (font_init_master(mlx));
}

int	font_write(char *word, t_data *game, t_font_setting f_setting)
{
	return (font_write_master(word, game, f_setting));
}

int	font_write_img(char *word, t_data *game, t_txtr *copy, t_font_setting f_s)
{
	game->cords.img_x = f_s.x;
	game->cords.img_y = f_s.y;
	return (font_write_to_im_master(word, game, copy, f_s));
}

t_font_setting	font_settings(int posx, int posy, int color, int identifier)
{
	t_font_setting font;

	font.x = posx;
	font.y = posy;
	font.color = color;
	font.identifier = identifier;
	return (font);
}

void	font_delete(t_data *game)
{
	int	letter;

	letter = 0;
	while (letter < 26)
	{
		mlx_destroy_image(game->mlx.mlx, game->font->xl_font.letter[letter].img);
		mlx_destroy_image(game->mlx.mlx, game->font->big_font.letter[letter].img);
		mlx_destroy_image(game->mlx.mlx,
							game->font->medium_font.letter[letter].img);
		mlx_destroy_image(game->mlx.mlx, game->font->small_font.letter[letter].img);
		letter++;
	}
	free(game->font->xl_font.letter);
	free(game->font->big_font.letter);
	free(game->font->medium_font.letter);
	free(game->font->small_font.letter);
	free(game->font);
}
