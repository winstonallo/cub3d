/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:42:17 by yannis            #+#    #+#             */
/*   Updated: 2024/01/22 17:42:26 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/button.h"

void			font_delete(t_data *temp);
void			gif_delete(t_data *temp, void *mlx);

int	int_exit_master(t_data *temp, int i)
{
	(void)i;
	button_delete_master(temp, temp->mlx.mlx);
	font_delete(temp);
	gif_delete(temp, temp->mlx.mlx);
	//free_game(temp);
	exit(0);
	return (0);
}

int	say_master(t_data *temp, int i)
{
	(void)temp;
	(void)i;
	write(1, "Hi. I got clicked\n", 18);
	return (0);
}