/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:50 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/18 17:04:38 by abied-ch         ###   ########.fr       */
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

void	get_hit_direction(t_line line, t_data *data)
{
	if (line.direction == VERTICAL)
		data->hit = SOUTH;
	else
		data->hit = EAST;
}

void	calculate_distance(t_data *data, t_line line1, t_line line2)
{
	float	min_dist1;
	float	min_dist2;	

	min_dist1 = dist(line1);
	min_dist2 = dist(line2);
	if (min_dist1 < min_dist2)
		set_shortest_line_vars(data, min_dist1, line1, line1.y1);
	else
		set_shortest_line_vars(data, min_dist2, line2, line2.x1);
	get_hit_direction(data->shortest_line, data);
}
