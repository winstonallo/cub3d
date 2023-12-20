/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_public.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:15:52 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/20 17:30:29 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	font_write_master(char *word, t_game *game, t_img *copy, t_font_setting f);
t_font	*font_init_master(void *mlx);
void	image_edit_master(t_game *g, t_img *base, t_img to_copy, int iden);

t_font	*font_init(void *mlx)
{
	return (font_init_master(mlx));
}

int	font_write(char *word, t_game *game, t_img *copy, t_font_setting f_setting)
{
	game->cords.img_x = f_setting.x;
	game->cords.img_y = f_setting.y;
	return (font_write_master(word, game, copy, f_setting));
}

t_font_setting	font_settings(int posx, int posy, int color, int identifier)
{
	t_font_setting font;

	font.x = posx;
	font.y = posy;
	font.color = color;
	font.identifier = identifier;
	printf("%d\n", color);
	return (font);
}

void	font_delete(t_game *game)
{
	int	letter;

	letter = 0;
	while (letter < 26)
	{
		mlx_destroy_image(game->mlx, game->font->xl_font.letter[letter].img);
		mlx_destroy_image(game->mlx, game->font->big_font.letter[letter].img);
		mlx_destroy_image(game->mlx,
							game->font->medium_font.letter[letter].img);
		mlx_destroy_image(game->mlx, game->font->small_font.letter[letter].img);
		letter++;
	}
	free(game->font->xl_font.letter);
	free(game->font->big_font.letter);
	free(game->font->medium_font.letter);
	free(game->font->small_font.letter);
	free(game->font);
}

void	image_edit(t_game *g, t_img *base, t_img to_copy, int identifier)
{
	image_edit_master(g, base, to_copy, identifier);
}