/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:34 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/19 14:23:21 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

float	dist(t_line line)
{
	return sqrt((line.x1 - line.x0) * (line.x1 - line.x0)
			+ (line.y1 - line.y0) * (line.y1 - line.y0));
}

void	calculate_distance(t_data *data, t_line line1, t_line line2)
{
	float	min_dist1;
	float	min_dist2;

	min_dist1 = dist(line1);
	min_dist2 = dist(line2);
	if (min_dist1 < min_dist2)
	{
		data->wall_color = 0xF4C2C2;
		data->min_distance = min_dist1;
		line1.scale = MAPSIZE;
		data->shortest_line = line1;
	}
	else
	{
		data->wall_color = 0xC154C1;
		data->min_distance = min_dist2;
		line2.scale = MAPSIZE;
		data->shortest_line = line2;
	}
}

void	get_line(t_line *line, t_raycast ray, t_data *data)
{
	line->x0 = data->player.x_pos * data->tile_width;
	line->y0 = data->player.y_pos * data->tile_height;
	line->x1 = ray.reach_x * data->tile_width;
	line->y1 = ray.reach_y * data->tile_height;
	line->scale = SCREEN;
}

void	draw_rays(t_data *data, float angle)
{
	t_line		v_line;
	t_line		h_line;
	t_raycast	vertical;
	t_raycast	horizontal;

	init_vars_horizontal(&horizontal, &data->player, angle);
	scan(&horizontal, data);
	init_vars_vertical(&vertical, &data->player, angle);
	scan(&vertical, data);
	get_line(&v_line, vertical, data);
	get_line(&h_line, horizontal, data);
	return (calculate_distance(data, v_line, h_line));
}


void	init_3d_lines(t_line *line1, int i, t_data *data)
{
	line1->x0 = i * ((float)SCREEN_WIDTH / 60);
	line1->x1 = i * ((float)SCREEN_WIDTH / 60);
	line1->y0 = data->line_offset;
	line1->y1 = data->line_height + data->line_offset;
	line1->scale = SCREEN;
}

void	raycast(t_data *data)
{
	t_line	line1;
	int		i;
	float	angle;	

	i = -1;
	angle = fmod(data->player.angle - DR * 30, 2 * PI);
	while (++i < FIELD_OF_VIEW)
	{
		data->min_distance = 100000;
		draw_rays(data, angle);
		draw_line(data, data->shortest_line, 0xffffff, 1);
		data->fisheye = data->player.angle - angle;
		data->fisheye = fmod(data->fisheye + PI, 2 * PI) - PI;
		data->min_distance *= cos(data->fisheye);
		data->line_height = SCREEN_HEIGHT / (data->min_distance / 4);
		if (data->line_height > SCREEN_HEIGHT)
			data->line_height = SCREEN_HEIGHT;
		data->line_offset = (SCREEN_HEIGHT2) - (data->line_height / 2);
		init_3d_lines(&line1, i, data);
		draw_line(data, line1, data->wall_color, 4);
		angle += DR;
		angle = fmod(angle, 2 * PI);
	}
	draw_map(data);
}
