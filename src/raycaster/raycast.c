/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:34:34 by abied-ch          #+#    #+#             */
/*   Updated: 2023/12/17 14:21:58 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/raycast.h"

float	dist(t_dist dist)
{
	return (sqrt((dist.x1 - dist.x0) + (dist.y1 - dist.y0)));
}

void	calculate_distance(t_raycast *ray, t_data *data)
{
	t_dist	distance;
	int		min_dist;

	distance.x0 = ray->map_x;
	distance.y0 = ray->map_y;
	distance.x1 = ray->reach_x;
	distance.y1 = ray->reach_y;
	// printf("x0: %f - y0: %f - x1: %f - y1: %f\n", distance.x0, distance.y0, distance.x1, distance.y1);
	min_dist = dist(distance);
	if (!data->min_distance || min_dist < data->min_distance)
		data->min_distance = min_dist;
}

void	draw_rays_horizontal(t_data *data)
{
	t_raycast	ray;
	t_player	*player;
	t_line		line;

	ray.loop_protection = -1;
	player = &data->player;
	ray.angle = player->angle;
	ray.r = -1;
	while (++ray.r < 1)
	{
		ray.max_depth = 0;
		ray.a_tan = -1 / tan(ray.angle);
		init_vars_horizontal(&ray, player, data);
		horizontal_scan(&ray, data);
	}
	line.x0 = player->x_pos * data->tile_width;// + data->tile_width / 2;
	line.y0 = player->y_pos * data->tile_height;// + data->tile_height / 2;
	line.x1 = (ray.reach_x * data->tile_width);// + data->tile_width / 2;;
	line.y1 = (ray.reach_y * data->tile_height);// + data->tile_height / 2;;
	draw_circle(data, line.x1, line.y1, 8);
	calculate_distance(&ray, data);
	draw_line(data, line, 0x39ff14, 4);
}

void	draw_rays_vertical(t_data *data)
{
	t_line		line;
	t_player	*player;
	t_raycast	ray;

	ray.loop_protection = -1;
	player = &data->player;
	ray.angle = player->angle;
	ray.r = -1;
	while (++ray.r < 1)
	{
		ray.max_depth = 0;
		ray.n_tan = -tan(ray.angle);
		init_vars_vertical(&ray, player, data);
		vertical_scan(&ray, data);
	}
	line.x0 = player->x_pos * data->tile_width;// + data->tile_width / 2;
	line.y0 = player->y_pos * data->tile_height;// + data->tile_height / 2;
	line.x1 = ray.reach_x * data->tile_width;// + data->tile_width / 2;
	line.y1 = ray.reach_y * data->tile_height;// + data->tile_height / 2;
	calculate_distance(&ray, data);
	draw_line(data, line, 0xff0000, 2);
}

void	raycast(t_data *data)
{
	data->error = SUCCESS;
	draw_rays_horizontal(data);
	draw_rays_vertical(data);
	if (data->error == NO_WALL_HIT){
		printf(BOLD);printf(RED);printf("\n----NO-WALL-HIT---\n\n");printf(RESET);	
	}
	// printf("MIN DISTANCE: %f\n", data->min_distance);
}
