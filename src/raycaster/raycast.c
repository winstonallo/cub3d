/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:34 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/17 23:25:12 by abied-ch         ###   ########.fr       */
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

t_line	draw_rays_horizontal(t_data *data, float angle)
{
	t_raycast	ray;
	t_player	*player;
	t_line		line;

	player = &data->player;
	ray.angle = angle;
	ray.max_depth = 0;
	ray.a_tan = -1 / tan(ray.angle);
	init_vars_horizontal(&ray, player);
	horizontal_scan(&ray, data);
	line.x0 = player->x_pos * data->tile_width;
	line.y0 = player->y_pos * data->tile_height;
	line.x1 = ray.reach_x * data->tile_width;
	line.y1 = ray.reach_y * data->tile_height;
	return (line);
}

t_line	draw_rays_vertical(t_data *data, float angle)
{
	t_line		line;
	t_player	*player;
	t_raycast	ray;

	player = &data->player;
	ray.angle = angle;
	ray.max_depth = 0;
	ray.n_tan = -tan(ray.angle);
	init_vars_vertical(&ray, player);
	vertical_scan(&ray, data);
	line.x0 = player->x_pos * data->tile_width;
	line.y0 = player->y_pos * data->tile_height;
	line.x1 = ray.reach_x * data->tile_width;
	line.y1 = ray.reach_y * data->tile_height;
	return (line);
}

void	init_3d_lines(t_line *line1, int i, t_data *data)
{
	line1->x0 = i * (SCREEN_WIDTH / 60);
	line1->x1 = i * (SCREEN_WIDTH / 60);
	line1->y0 = data->line_offset;
	line1->y1 = data->line_height + data->line_offset;
}

void	raycast(t_data *data)
{
	t_line	vertical;
	t_line	horizontal;
	t_line	line1;
	int		i;
	float	angle;	

	i = -1;
	data->error = SUCCESS;
	angle = data->player.angle - DR * 30;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	while (++i < FIELD_OF_VIEW)
	{
		data->min_distance = 100000;
		vertical = draw_rays_vertical(data, angle);
		horizontal = draw_rays_horizontal(data, angle);
		calculate_distance(data, horizontal, vertical);
		draw_line(data, data->shortest_line, 0xffffff, 1);
		float fisheye = data->player.angle - angle;
		fisheye = fmod(fisheye + PI, 2 * PI) - PI;
		data->min_distance *= cos(fisheye);
		data->line_height = SCREEN_HEIGHT2 / (data->min_distance / 2);
		if (data->line_height > SCREEN_HEIGHT2)
			data->line_height = SCREEN_HEIGHT2;
		data->line_offset = (SCREEN_HEIGHT2) - (data->line_height / 2);
		init_3d_lines(&line1, i, data);
		draw_line(data, line1, data->wall_color, 4);
		angle += DR;
		angle = fmod(angle, 2 * PI);
	}
	draw_map(data);
}
