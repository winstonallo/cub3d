/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:07 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/21 19:14:58 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"
#include <stdio.h>
#include <stdlib.h>

static int	turn(int direction, t_data *data)
{
	if (direction == TURN_RIGHT)
	{
		data->player.angle += TURN_SPEED * DR;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		data->player.x_dir = cos(data->player.angle) * TURN_SPEED;
		data->player.y_dir = sin(data->player.angle) * TURN_SPEED;
	}
	else if (direction == TURN_LEFT)
	{
		data->player.angle -= TURN_SPEED * DR;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
		data->player.x_dir = cos(data->player.angle) * TURN_SPEED;
		data->player.y_dir = sin(data->player.angle) * TURN_SPEED;
	}
	new_image(data);
	return (EXIT_SUCCESS);
}

static int	check_collision(t_data *data, float new_x, float new_y)
{
	int	pos;
	int	neg;

	pos = (int)(new_y + COLL_SENS) * data->map_width + (int)(new_x + COLL_SENS);
	neg = (int)(new_y - COLL_SENS) * data->map_width + (int)(new_x - COLL_SENS);
	if (data->map[pos] != 1 && data->map[neg] != 1)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	adjust(t_data *data, float x_dir, float y_dir)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x_pos + x_dir * SPEED;
	new_y = data->player.y_pos + y_dir * SPEED;
	if (!check_collision(data, new_x, new_y))
	{
		data->player.x_pos = new_x;
		data->player.y_pos = new_y;
	}
	else
	{
		if (!check_collision(data, data->player.x_pos, new_y))
			data->player.y_pos = new_y;
		if (!check_collision(data, new_x, data->player.y_pos))
			data->player.x_pos = new_x;
	}
	new_image(data);
	return (EXIT_SUCCESS);
}

int	event(int key, t_data *data)
{
	if (key == 13)
		return (adjust(data, data->player.x_dir, data->player.y_dir));
	else if (key == 1)
		return (adjust(data, -data->player.x_dir, -data->player.y_dir));
	else if (key == E)
		return (adjust(data, -data->player.y_dir, data->player.x_dir));
	else if (key == Q)
		return (adjust(data, data->player.y_dir, -data->player.x_dir));
	else if (key == 0)
		return (turn(TURN_LEFT, data));
	else if (key == 2)
		return (turn(TURN_RIGHT, data));
	else if (key == 53)
		exit_success(data);
	return (EXIT_SUCCESS);
}
