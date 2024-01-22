/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:34:56 by yannis            #+#    #+#             */
/*   Updated: 2024/01/18 02:41:02 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/button.h"

/*	This function adds a function (action) to a button in case of beeing clicked
	1 Parameter: function. Default type of a function should be int.
			Example: int example_function()
			If you want to use a function with diffrent type. Prototype as followed:
				button_add_function((int (*)(t_temp *, int))function, game, i)
	2 Parameter: Main struct of the game where the mlx and win is located*/
int	button_add_function_master(int (*function)(t_data *, int i), t_data *game, int i)
{
	game->button[i]->function = function;
	return (0);
}

/*	This function changes the position of Button on the window
	1 Parameter: Main struct of the game where the mlx and win is located
	2 Parameter: Position of the horizontal starting point of the button
	3 Parameter: Position of the vertical starting point of the button
	4 Parameter: identifier of what button you want to edit*/
int	button_change_position_master(t_data *game, int posx, int posy, int identifier)
{
	game->button[identifier]->posx = posx;
	game->button[identifier]->posy = posy;
	game->button[identifier]->iden = identifier;
	game->button[identifier]->button_clicked = 0;
	if (game->button[identifier]->activate == 1)
		mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
			game->button[1]->img[0].img, posx, posy);
	return (0);
}

int	button_switch_master(t_data *game, int i)
{
	if (!(i < game->button_index))
		return (-1);
	if (game->button[i]->activate == 0)
		game->button[i]->activate = 1;
	else
		game->button[i]->activate = 0;
	return (0);
}