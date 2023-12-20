/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:33:07 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/20 13:50:31 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"
#include <stdio.h>
#include <stdlib.h>

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

int	get_direction(t_data *data)
{
	if (data->player.angle > (7 * PI) / 4 || data->player.angle < PI / 4)
		return (NORTH);
	else if (data->player.angle > PI / 4 && data->player.angle < (3 * PI) / 4)
		return (EAST);
	else if (data->player.angle > (3 * PI) / 4 && data->player.angle < (5 * PI) / 4)
		return (SOUTH);
	else if (data->player.angle > (5 * PI) / 4 && data->player.angle < (7 * PI) / 4)
		return (WEST);
    return 0;
}

void	slide_on_walls(t_data *data)
{
	int direction;

	direction = get_direction(data);
	if (direction == NORTH || direction == SOUTH)
		data->player.x_pos += data->player.x_dir * SPEED;
	else if (direction == EAST || direction == WEST)
		data->player.y_pos += data->player.y_dir * SPEED;
}

static int	check_collision(t_data *data, float new_x, float new_y)
{
	int map_pos;
	int map_neg;
	
	map_pos = (int)(new_y + COLL_SENS) * data->map_width + (int)(new_x + COLL_SENS);
	map_neg = (int)(new_y - COLL_SENS) * data->map_width + (int)(new_x - COLL_SENS);
	if (data->map[map_pos] == 0 && data->map[map_neg] == 0){
		return (EXIT_SUCCESS);
	}
	printf("map_pos: %d\n", map_pos);
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
        slide_on_walls(data);
	new_image(data);
	return (EXIT_SUCCESS);
}

int	event(int key, t_data *data)
{
	if (key == W)
		return (adjust(data, data->player.x_dir, data->player.y_dir));
	else if (key == S)
		return (adjust(data, -data->player.x_dir, -data->player.y_dir));
	else if (key == E)
		return (adjust(data, -data->player.y_dir, data->player.x_dir));
	else if (key == Q)
		return (adjust(data, data->player.y_dir, -data->player.x_dir));
	else if (key == A)
		return (turn(TURN_LEFT, data));
	else if (key == D)
		return (turn(TURN_RIGHT, data));
	else if (key == ESCAPE)
		exit_success(data);
	return (EXIT_SUCCESS);
}
