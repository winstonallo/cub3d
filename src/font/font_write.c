/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:32:56 by yatabay           #+#    #+#             */
/*   Updated: 2024/01/18 01:48:46 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/font.h"

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

static	int	font_to_img(t_font_setting fo, t_game *ga, int integer, t_img *base)
{
	if (fo.identifier == 4)
	{
		ga->font->xl_font.letter[integer].color = fo.color;
		image_edit(ga, base, ga->font->xl_font.letter[integer], 1);
		return (ga->font->xl_font.letter[integer].width);
	}
	else if (fo.identifier == 3)
	{
		ga->font->big_font.letter[integer].color = fo.color;
		image_edit(ga, base, ga->font->big_font.letter[integer], 1);
		return (ga->font->big_font.letter[integer].width);
	}
	else if (fo.identifier == 2)
	{
		ga->font->medium_font.letter[integer].color = fo.color;
		image_edit(ga, base, ga->font->medium_font.letter[integer], 1);
		return (ga->font->medium_font.letter[integer].width);
	}
	else if (fo.identifier == 1)
	{
		ga->font->small_font.letter[integer].color = fo.color;
		image_edit(ga, base, ga->font->small_font.letter[integer], 1);
		return (ga->font->small_font.letter[integer].width);
	}
	return (0);
}

void	font_write_to_image(t_game *ga, t_img *ba, char *to, t_font_setting fo)
{
	int	integer;
	int	spacing;
	int	shift;
	int	i;

	i = 0;
	shift = ga->cords.img_x;
	spacing = 0;
	while (to[i])
	{
		if (to[i] == 32)
			spacing += space(fo.identifier);
		else
		{
			integer = to[i] - 97;
			spacing += font_to_img(fo, ga, integer, ba);
		}
		ga->cords.img_x = spacing + shift;
		i++;
	}
}

void	font_write_to_display(t_game *ga, char *to, t_font_setting fo)
{
	int	character;
	int spacing;
	int	pos;

	pos = -1;
	spacing = 0;
	while (to[++pos])
	{
		if (to[pos] == 32)
			spacing += space(fo.identifier);
		if (to[pos] >= 'a' && to[pos] <= 'z')
		{
			character = to[pos] - 97;
			if (fo.identifier == 4)
			{
				mlx_put_image_to_window(ga->mlx, ga->win,
					ga->font->xl_font.letter[character].img, fo.x + spacing, fo.y);
				spacing += ga->font->xl_font.letter[character].width;
			}
			else if (fo.identifier == 3)
			{
				mlx_put_image_to_window(ga->mlx, ga->win,
					ga->font->big_font.letter[character].img, fo.x + spacing, fo.y);
				spacing += ga->font->big_font.letter[character].width;
			}
			else if (fo.identifier == 2)
			{
				mlx_put_image_to_window(ga->mlx, ga->win,
					ga->font->medium_font.letter[character].img, fo.x + spacing, fo.y);
				spacing += ga->font->medium_font.letter[character].width;
			}
			else if (fo.identifier == 1)
			{
				mlx_put_image_to_window(ga->mlx, ga->win,
					ga->font->small_font.letter[character].img, fo.x + spacing, fo.y);
				spacing += ga->font->small_font.letter[character].width;
			}
		}
	}
}
