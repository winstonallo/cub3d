/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:50 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/18 17:32:42 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	adjust_vars(t_data *data, float angle)
{
	data->fisheye = cos(angle - data->player.angle);
	data->min_distance *= (data->fisheye);
	data->line_height = SCREEN_HEIGHT / (data->min_distance / 20);
	if (data->line_height > SCREEN_HEIGHT)
		data->line_height = SCREEN_HEIGHT;
	data->line_offset = ((float)SCREEN_HEIGHT / 2)
		- (data->line_height * WALL_HEIGHT);
}

void	calculate_distance(t_data *data, t_line line1, t_line line2)
{
	float	min_dist1;
	float	min_dist2;

	min_dist1 = dist(line1);
	min_dist2 = dist(line2);
	if (min_dist1 < min_dist2)
	{
		set_shortest_line_vars(data, min_dist1, line1, line1.y1);
		data->hit = (data->shortest_line.x1 - data->shortest_line.x0) >= 0 ? SOUTH : NORTH;
	}
	else
	{
		set_shortest_line_vars(data, min_dist2, line2, line2.x1);
		data->hit = (data->shortest_line.y1 - data->shortest_line.y0) >= 0 ? EAST : WEST;
	}
	// get_hit_direction(data->shortest_line, data);
}
