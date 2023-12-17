/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:07 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/17 17:39:16 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

static int	turn(int direction, t_data *data)
{
	if (direction == TURN_RIGHT)
	{
		data->player.angle += 0.1;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		data->player.x_dir = cos(data->player.angle) * 5;
		data->player.y_dir = sin(data->player.angle) * 5;
	}
	else if (direction == TURN_LEFT)
	{
		data->player.angle -= 0.1;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
		data->player.x_dir = cos(data->player.angle) * 5;
		data->player.y_dir = sin(data->player.angle) * 5;
	}
	new_image(data);
	return (EXIT_SUCCESS);
}

static int	move(int direction, t_data *data)
{
	if (direction == UP)
	{
		data->player.x_pos += data->player.x_dir * SPEED;
		data->player.y_pos += data->player.y_dir * SPEED;
	}
	else if (direction == DOWN)
	{
		data->player.x_pos -= data->player.x_dir * SPEED;
		data->player.y_pos -= data->player.y_dir * SPEED;
	}
    if (direction == STRAFE_RIGHT)
    {
        data->player.x_pos -= data->player.y_dir * SPEED;
        data->player.y_pos += data->player.x_dir * SPEED;
    }
    else if (direction == STRAFE_LEFT)
    {
        data->player.x_pos += data->player.y_dir * SPEED;
        data->player.y_pos -= data->player.x_dir * SPEED;
    }
	new_image(data);
	return (EXIT_SUCCESS);
}

int	event(int key, t_data *data)
{
	if (key == W)
		return (move(UP, data));
	else if (key == S)
		return (move(DOWN, data));
	else if (key == E)
		return (move(STRAFE_RIGHT, data));
	else if (key == Q)
		return (move(STRAFE_LEFT, data));
	else if (key == A)
		return (turn(TURN_LEFT, data));
	else if (key == D)
		return (turn(TURN_RIGHT, data));
	else if (key == ESCAPE)
		exit_success(data);
	return (EXIT_SUCCESS);
}
