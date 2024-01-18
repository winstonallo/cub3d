/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:34 by abied-ch          #+#    #+#             */
/*   Updated: 2024/01/18 16:59:03 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

void	init_vars_horizontal(t_raycast *h_ray, t_player *player, float angle)
{
	h_ray->max_depth = 0;
	h_ray->a_tan = -1 / tan(angle);
	h_ray->direction = HORIZONTAL;
	if (angle > PI)
	{
		h_ray->reach_y = (int)player->y_pos - 0.0001;
		h_ray->inc_y = -1;
	}
	else if (angle < PI)
	{
		h_ray->reach_y = (int)player->y_pos + 1;
		h_ray->inc_y = 1;
	}
	else
	{
		h_ray->reach_y = player->y_pos;
		h_ray->inc_y = 0;
		h_ray->max_depth = 33;
	}
	h_ray->reach_x = (player->y_pos - h_ray->reach_y)
		* h_ray->a_tan + player->x_pos;
	h_ray->inc_x = -h_ray->inc_y * (h_ray->a_tan);
}

void	init_vars_vertical(t_raycast *v_ray, t_player *player, float angle)
{
	v_ray->max_depth = 0;
	v_ray->n_tan = -tan(angle);
	v_ray->direction = VERTICAL;
	if (angle > P2 && angle < P3)
	{
		v_ray->reach_x = (int)player->x_pos - 0.0001;
		v_ray->inc_x = -1;
	}
	else if (angle < P2 || angle > P3)
	{
		v_ray->reach_x = (int)player->x_pos + 1;
		v_ray->inc_x = 1;
	}
	else
	{
		v_ray->inc_x = 0;
		v_ray->reach_x = player->x_pos;
		v_ray->max_depth = 33;
	}
	v_ray->reach_y = (player->x_pos - v_ray->reach_x)
		* v_ray->n_tan + player->y_pos;
	v_ray->inc_y = -v_ray->inc_x * v_ray->n_tan;
}

void	scan(t_raycast *ray, t_data *data, int max)
{
	while (ray->max_depth < max)
	{
		ray->map_x = ((int)ray->reach_x);
		ray->map_y = ((int)ray->reach_y);
		ray->map_pos = ray->map_y * data->map_width + ray->map_x;
		if (collision(data, ray->reach_x, ray->reach_y))
			return ;
		else
		{
			ray->reach_x += ray->inc_x;
			ray->reach_y += ray->inc_y;
			ray->max_depth++;
		}
	}
}

void	draw_rays(t_data *data, float angle)
{
	t_line		v_line;
	t_line		h_line;
	t_raycast	vertical;
	t_raycast	horizontal;

	init_vars_horizontal(&horizontal, &data->player, angle);
	init_vars_vertical(&vertical, &data->player, angle);
	scan(&horizontal, data, data->map_width);
	scan(&vertical, data, data->map_width);
	get_line(&h_line, horizontal, data);
	get_line(&v_line, vertical, data);
	calculate_distance(data, v_line, h_line);
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
	normalize_angle(&data->angle, (-FIELD_OF_VIEW / 2));
	while (++x < SCREEN_WIDTH)
	{
		data->hit_pos = MAX_DIST;
		data->min_distance = MAX_DIST;
		draw_rays(data, data->angle);
		adjust_vars(data, data->angle);
		get_3d_line(&line, x, data);
		line.wall_height = line.y1 - line.y0;
		set_texture(data, &texture);
		draw_texture(data, x, line, &texture);
		normalize_angle(&data->angle, FIELD_OF_VIEW / (SCREEN_WIDTH));
	}
	draw_map(data);
	draw_player(data);
}
