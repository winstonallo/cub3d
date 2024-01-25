/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:07 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 18:16:21 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

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

static bool	check_collision(t_data *data, double new_x, double new_y)
{
	int	tl;
	int	tr;
	int	bl;
	int	br;

	tl = (int)(new_y - COLL_SENS) *data->map_width + (int)(new_x - COLL_SENS);
	tr = (int)(new_y - COLL_SENS) *data->map_width + (int)(new_x + COLL_SENS);
	bl = (int)(new_y + COLL_SENS) *data->map_width + (int)(new_x - COLL_SENS);
	br = (int)(new_y + COLL_SENS) *data->map_width + (int)(new_x + COLL_SENS);
	if (is_not_wall(data->map[tl], data->map[tr], data->map[bl], data->map[br]))
		return (false);
	return (true);
}

static void	slide_on_walls(t_data *data, double new_x, double new_y)
{
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
}

static int	adjust(t_data *data, double x_dir, double y_dir)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x_pos + x_dir * SPEED;
	new_y = data->player.y_pos + y_dir * SPEED;
	data->player.x_prev = data->player.x_pos;
	data->player.y_prev = data->player.y_pos;
	slide_on_walls(data, new_x, new_y);
	new_image(data);
	return (EXIT_SUCCESS);
}

int	event(int key, t_data *data)
{
	if (key == W)
		return (adjust(data, data->player.x_dir, data->player.y_dir));
	else if (key == S)
		return (adjust(data, -data->player.x_dir, -data->player.y_dir));
	else if (key == D)
		return (adjust(data, -data->player.y_dir, data->player.x_dir));
	else if (key == A)
		return (adjust(data, data->player.y_dir, -data->player.x_dir));
	else if (key == 65361)
		return (turn(TURN_LEFT, data));
	else if (key == 65363)
		return (turn(TURN_RIGHT, data));
	else if (key == ESCAPE)
		exit_success(data);
	return (EXIT_SUCCESS);
}
