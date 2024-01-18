/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:42:17 by yannis            #+#    #+#             */
/*   Updated: 2024/01/18 01:47:02 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/button.h"

void			font_delete(t_game *temp);
void			gif_delete(t_game *temp, void *mlx);

int	int_exit_master(t_game *temp, int i)
{
	int	pos;

	pos = 0;
	(void)i;
	button_delete_master(temp, temp->mlx);
	font_delete(temp);
	gif_delete(temp, temp->mlx);
	free_game(temp);
	exit(0);
	return (0);
}

int	say_master(t_game *temp, int i)
{
	(void)temp;
	(void)i;
	write(1, "Hi. I got clicked\n", 18);
	return (0);
}