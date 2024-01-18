/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:50 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/18 16:49:32 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"
#include <stdio.h>

void	get_line(t_line *line, t_raycast ray, t_data *data)
{
	line->x0 = data->player.x_pos * data->x_scale;
	line->y0 = data->player.y_pos * data->y_scale;
	line->x1 = ray.reach_x * data->x_scale;
	line->y1 = ray.reach_y * data->y_scale;
	line->direction = ray.direction;
	if (ray.direction == VERTICAL)
	{
		line->y_inc = ray.inc_y;
		line->x_inc = 0;
	}
	else
	{
		line->x_inc = ray.inc_x;
		line->y_inc = 0;
	}
	line->scale = SCREEN;
}

void	get_3d_line(t_line *line, int i, t_data *data)
{
	line->x0 = i * ((float)SCREEN_WIDTH / 120);
	line->x1 = i * ((float)SCREEN_WIDTH / 120);
	line->y0 = data->line_offset;
	line->y1 = data->line_height * ((float)SCREEN_HEIGHT2 / 120)
		+ data->line_offset;
	line->wall_height = data->line_height;
	line->scale = SCREEN;
}

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

void	set_shortest_line(t_data *data, t_line line, float min_dist)
{
	data->min_distance = min_dist;
	data->shortest_line = line;
	data->shortest_line.scale = MAPSIZE;
	data->hit_pos = line.y1;
}

void	calculate_distance(t_data *data, t_line line1, t_line line2)
{
	float	min_dist1;
	float	min_dist2;	

	min_dist1 = dist(line1);
	min_dist2 = dist(line2);
	if (min_dist1 < min_dist2)
		set_shortest_line(data, line1, min_dist1);
	else
		set_shortest_line(data, line2, min_dist2);
	get_hit_direction(data->shortest_line, data);
}
