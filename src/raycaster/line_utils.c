/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:50:31 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/18 17:17:56 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	set_shortest_line_vars(t_data *data, float min, t_line line, float hit)
{
	data->min_distance = min;
	data->hit_pos = hit;
	line.scale = MAPSIZE;
	data->hit = line.hit;
	data->shortest_line = line;
}

void	get_line(t_line *line, t_raycast ray, t_data *data)
{
	line->x0 = data->player.x_pos * data->x_scale;
	line->y0 = data->player.y_pos * data->y_scale;
	line->x1 = ray.reach_x * data->x_scale;
	line->y1 = ray.reach_y * data->y_scale;
	line->direction = ray.direction;
	line->hit = ray.hit;
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
