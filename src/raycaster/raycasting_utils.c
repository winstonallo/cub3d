/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:50 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 12:47:39 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	adjust_vars(t_data *data, double angle)
{
	data->fisheye = cos(angle - data->player.angle);
	data->min_distance *= (data->fisheye);
	data->line_height = SCREEN_HEIGHT / (data->min_distance / 20);
	if (data->line_height > SCREEN_HEIGHT)
		data->line_height = SCREEN_HEIGHT;
	data->line_offset = ((double)SCREEN_HEIGHT / 2)
		- (data->line_height * WALL_HEIGHT);
}

void	get_hit_direction(t_data *data, int direction, double side)
{
	if (direction == VERTICAL)
	{
		if (side >= 0)
			data->hit = SOUTH;
		else
			data->hit = NORTH;
	}
	else
	{
		if (side >= 0)
			data->hit = EAST;
		else
			data->hit = WEST;
	}
}

void	calculate_distance(t_data *data, t_line line1, t_line line2)
{
	double	min_dist1;
	double	min_dist2;

	min_dist1 = dist(line1);
	min_dist2 = dist(line2);
	if (min_dist1 < min_dist2)
	{
		set_shortest_line(data, min_dist1, line1, line1.y1);
		get_hit_direction(data, HORIZONTAL, line1.x1 - line1.x0);
	}
	else
	{
		set_shortest_line(data, min_dist2, line2, line2.x1);
		get_hit_direction(data, VERTICAL, line2.y1 - line2.y0);
	}
}
