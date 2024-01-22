/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yatabay <yatabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 00:47:59 by yannis            #+#    #+#             */
/*   Updated: 2024/01/22 14:18:53 by yatabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/elevator.h"

void	change_floor(t_data *data)
{
	float	p_x_temp;
	float	p_y_temp;

	if (data->argc == 0)
		return ;
	lift_switch(data);
	p_x_temp = data->player.x_pos;
	p_y_temp = data->player.y_pos;
	data->player.x_pos = data->player.x_oldpos;
	data->player.y_pos = data->player.y_oldpos;
	data->player.x_oldpos = p_x_temp;
	data->player.y_oldpos = p_y_temp;
}

void	change_map_settings(t_data *data)
{
	int	width_temp;
	int	height_temp;

	width_temp = data->map_width_old;
	height_temp = data->map_height_old;
	data->map_width_old = data->map_width;
	data->map_height_old = data->map_height;
	data->map_width = width_temp;
	data->map_height = height_temp;
}

void	lift_switch(t_data *data)
{

	data->gif[0]->active = !data->gif[0]->active;
	data->gif[1]->active = !data->gif[1]->active;
	data->elev.active = 1;
	// data->gif[2]->active = 1;
	// data->gif[3]->active = 1;
	if (data->elev.floor == 0)
	{
		data->map = data->maps[1];
		data->elev.floor = 1;
	}
	else
	{
		data->map = data->maps[0];
		data->elev.floor = 0;
	}
	change_map_settings(data);
}
