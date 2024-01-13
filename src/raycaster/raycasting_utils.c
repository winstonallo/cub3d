/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:50 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/13 18:31:46 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"
#include <stdio.h>

bool	collision(t_data *data, float new_x, float new_y)
{
	int	map_pos;

	map_pos = (int)new_y * data->map_width + (int)new_x;
	if (map_pos < 0 || map_pos > data->map_width * data->map_height)
		return (true);
	if (data->map[map_pos] != 1)
		return (false);
	return (true);
}

void	get_line(t_line *line, t_raycast ray, t_data *data)
{
	line->x0 = data->player.x_pos * data->x_scale;
	line->y0 = data->player.y_pos * data->y_scale;
	line->x1 = ray.reach_x * data->x_scale;
	line->y1 = ray.reach_y * data->y_scale;
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
	data->line_height = SCREEN_HEIGHT / (data->min_distance / 12);
	if (data->line_height > SCREEN_HEIGHT)
		data->line_height = SCREEN_HEIGHT;
	data->line_offset = ((float)SCREEN_HEIGHT / 2)
		- (data->line_height * WALL_HEIGHT);
}

t_dir get_hit_direction(t_player* player, int idk)
{
	if (!idk)
	{
		if (player->angle >= M_PI/4 && player->angle < 3*M_PI/4)
    	    return NORTH;
		else
	        return WEST;
	}
	else
	{
    	if (player->angle >= 5*M_PI/4 && player->angle < 7*M_PI/4)
        	return SOUTH;
    	else
        	return EAST;
	}
}

void	calculate_distance(t_data *data, t_line line1, t_line line2)
{
	float	min_dist1;
	float	min_dist2;	

	min_dist1 = dist(line1);
	min_dist2 = dist(line2);
	if (min_dist1 < min_dist2)
	{
		data->hit = get_hit_direction(&data->player, 0);
		data->min_distance = min_dist1;
		data->hit_pos = line1.y1;
		line1.scale = MAPSIZE;
		data->shortest_line = line1;
	}
	else
	{
		data->hit = get_hit_direction(&data->player, 1);
		data->min_distance = min_dist2;
		data->hit_pos = line2.x1;
		line2.scale = MAPSIZE;
		data->shortest_line = line2;
	}
}
