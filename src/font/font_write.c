/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:32:56 by yatabay           #+#    #+#             */
/*   Updated: 2023/12/19 23:25:37 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

void	font_to_lower(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		word[i] = ft_tolower(word[i]);
		i++;
	}
}

static	int	space(int identifier)
{
	int	spacing;

	if (identifier == 4)
		spacing = 40;
	else if (identifier == 3)
		spacing = 25;
	else if (identifier == 2)
		spacing = 20;
	else if (identifier == 1)
		spacing = 10;
	else
		spacing = 0;
	return (spacing);
}

static	int	font_to_img(int identifier, t_game *game, int integer, t_img *base)
{
	int	spacing;

	spacing = 0;
	if (identifier == 4)
	{
		image_edit(game, base, game->font->xl_font.letter[integer], 1);
		spacing += game->font->xl_font.letter[integer].width;
	}
	else if (identifier == 3)
	{
		image_edit(game, base, game->font->big_font.letter[integer], 1);
		spacing += game->font->big_font.letter[integer].width;
	}
	else if (identifier == 2)
	{
		image_edit(game, base, game->font->medium_font.letter[integer], 1);
		spacing += game->font->medium_font.letter[integer].width;
	}
	else if (identifier == 1)
	{
		image_edit(game, base, game->font->small_font.letter[integer], 1);
		spacing += game->font->small_font.letter[integer].width;
	}
	return (spacing);
}

void	font_write_to_image(t_game *game, t_img *base, char *to_write, int iden)
{
	int	integer;
	int	spacing;
	int	shift;
	int	i;

	i = 0;
	shift = game->cords.img_x;
	spacing = 0;
	while (to_write[i])
	{
		if (to_write[i] == 32)
			spacing += space(iden);
		else
		{
			integer = to_write[i] - 97;
			spacing += font_to_img(iden, game, integer, base);
		}
		game->cords.img_x = spacing + shift;
		i++;
	}
}
