/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:11:02 by yannis            #+#    #+#             */
/*   Updated: 2024/01/18 01:46:46 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/button.h"

void	display_button(t_game *game, int i, int lap, int inc)
{
	int	second;

	second = 0;
	while (second < game->button_index)
	{
		if (i != second && game->button[second]->activate == 1)
			mlx_put_image_to_window(game->mlx, game->win, game->button[second]->img[0].img, game->button[second]->posx, game->button[second]->posy);
		second++;
	}
	if (game->button[i]->activate == 1)
	{
		if (inc < 9)
			mlx_put_image_to_window(game->mlx, game->win, game->button[i]->img[inc].img, game->button[i]->posx + inc, game->button[i]->posy + inc);
		else
			mlx_put_image_to_window(game->mlx, game->win, game->button[i]->img[8 - lap].img, game->button[i]->posx + 8 - lap, game->button[i]->posy + 8 - lap);
	}
}

int	mouse_actions(int (*function)(t_game *, int i), t_game *game, int i)
{
	int	status;

	status = function(game, i);
	return (status);
}

int	button_animation_master(void *data)
{
	static	int	inc;
	static	int	lap;
	static	int	active;
	static	int	i;
	t_game		*game;
	int			status;

	game = data;
	if (game->clicked == 0)
		return (0);
	while (inc == 0 && i < game->button_index)
	{
		if (game->button[i]->button_clicked == 1)
		{
			active = 1;
			break ;
		}
		i++;
	}
	if (active == 0)
		return (0);
	status = 0;
	display_button(game, i, lap, inc);
	if (inc > 8)
		lap++;
	inc++;
	if (inc == 17)
	{
		active = 0;
		lap = 0;
		inc = 0;
		if (!(game == NULL || game->button[i] == NULL || game->button[i]->function == NULL))
			if (game->button[i]->button_clicked == 1 && game->button[i]->activate == 1)
				status = mouse_actions(game->button[i]->function, game, i);
		i = 0;
		game->button[i]->button_clicked = 0;
		game->clicked = 0;
	}
	return (status);
}
