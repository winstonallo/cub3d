/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:34 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/17 19:46:30 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

float	dist(t_line line)
{
	return sqrt((line.x1 - line.x0) * (line.x1 - line.x0)
			+ (line.y1 - line.y0) * (line.y1 - line.y0));
}

void	calculate_distance(t_data *data, t_line line)
{
	float	min_dist;

	min_dist = dist(line);
	if (min_dist < data->min_distance)
	{
		data->min_distance = min_dist;
		data->shortest_line = line;
	}
}

t_line	draw_rays_horizontal(t_data *data, float angle)
{
	t_raycast	ray;
	t_player	*player;
	t_line		line;

	player = &data->player;
	ray.angle = angle;
	ray.a_tan = -1 / tan(ray.angle);
	init_vars_horizontal(&ray, player, data);
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
	init_vars_vertical(&ray, player, data);
	vertical_scan(&ray, data);
	line.x0 = player->x_pos * data->tile_width;
	line.y0 = player->y_pos * data->tile_height;
	line.x1 = ray.reach_x * data->tile_width;
	line.y1 = ray.reach_y * data->tile_height;
	return (line);
}

void	raycast(t_data *data)
{
	t_line	vertical;
	t_line	horizontal;
	int		i;
	float	angle;	

	i = -1;
	data->error = SUCCESS;
	// angle = data->player.angle - DR * 30;
	// if (angle < 0)
	// 	angle += 2 * PI;
	// if (angle > 2 * PI)
	// 	angle -= 2 * PI;
	angle = 0;
	while (++i < 1)
	{
		data->min_distance = 100000;
		vertical = draw_rays_vertical(data, data->player.angle);
		horizontal = draw_rays_horizontal(data, data->player.angle);
		// calculate_distance(data, horizontal);
		// calculate_distance(data, vertical);
		draw_line(data, vertical, 0x00ff00, 4);
		draw_line(data, horizontal, 0xff0000, 1);
		// angle += DR;
		// if (angle < 0)
		// 	angle += 2 * PI;
		// if (angle > 2 * PI)
		// 	angle -= 2 * PI;
	}
}
