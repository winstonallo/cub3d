/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 01:11:02 by yannis            #+#    #+#             */
/*   Updated: 2024/01/18 02:45:10 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/button.h"

void	display_button(t_data *game, int i, int lap, int inc)
{
	int	second;

	second = 0;
	while (second < game->button_index)
	{
		if (i != second && game->button[second]->activate == 1)
			mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->button[second]->img[0].img, game->button[second]->posx, game->button[second]->posy);
		second++;
	}
	if (game->button[i]->activate == 1)
	{
		if (inc < 9)
			mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->button[i]->img[inc].img, game->button[i]->posx + inc, game->button[i]->posy + inc);
		else
			mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->button[i]->img[8 - lap].img, game->button[i]->posx + 8 - lap, game->button[i]->posy + 8 - lap);
	}
}

int	mouse_actions(int (*function)(t_data *, int i), t_data *game, int i)
{
	int	status;

	status = function(game, i);
	return (status);
}
