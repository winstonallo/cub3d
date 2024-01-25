/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:34 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/25 12:45:05 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	raycast_init(t_data *data, double angle)
{
	horizontal_vars_init(&data->h_ray, &data->player, angle);
	vertical_vars_init(&data->v_ray, &data->player, angle);
}

void	perform_scan(t_data *data)
{
	scan(&data->h_ray, data, data->map_height);
	scan(&data->v_ray, data, data->map_width);
}

void	get_shortest_line(t_data *data)
{
	t_line		v_line;
	t_line		h_line;

	get_line(&v_line, data->v_ray, data);
	get_line(&h_line, data->h_ray, data);
	calculate_distance(data, v_line, h_line);
}

static void	throw_rays(t_data *data, double angle)
{
	raycast_init(data, angle);
	perform_scan(data);
	get_shortest_line(data);
	draw_line(data, data->shortest_line, HEXA_RED, 1);
}

void	raycast(t_data *data)
{
	int			x;
	t_line		line;
	t_txtr		texture;

	x = -1;
	draw_background(data);
	data->angle = data->player.angle;
	normalize_angle(&data->angle, (-FOV_INCREMENT / 2));
	while (++x < SCREEN_WIDTH)
	{
		data->hit_pos = MAX_DIST;
		data->min_distance = MAX_DIST;
		throw_rays(data, data->angle);
		adjust_vars(data, data->angle);
		get_3d_line(&line, x, data);
		line.wall_height = line.y1 - line.y0;
		set_texture(data, &texture);
		draw_texture(data, x, line, &texture);
		normalize_angle(&data->angle, FOV_INCREMENT / SCREEN_WIDTH);
	}
	draw_map(data);
	draw_player(data);
}
